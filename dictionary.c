/**
 * @file
 * @section LEÍRÁS
 * A fájlban vannak kezelve a szavak, beolvassa őket és lánvolja egy listába
 * */
#include "dictionary.h"
#include "string.h"
#include "debugmalloc.h"
#include "time.h"

/**
 * Konstans, ami tárolja a szavak hosszát, nehézség szerint indexelve
 * */
static const int len[3]={4,6,9};

/**
 * Konstans, ami a nyelvekhez tartozó szótárak elérési helyét tárolja
 * */
static const char* files[2]={"szotar/szavak_magyar.txt","szotar/szavak_angol.txt"};

/**
 * A függvény felszabadítja a szavak lámncolt listáját
 * @param Dictionary fogad egy Szótár változót, aminek eleme a szavak listája
 * @return nincs
 * */
static void clear_pool(DictionaryVars* Dictionary){
    Words* temp;
    while(Dictionary->wordpool!=NULL){
        temp = Dictionary->wordpool;
        Dictionary->wordpool=Dictionary->wordpool->next;
        free(temp->word);
        free(temp);
    }
}

/**
 * A függvény beolvassa a fájlt, és a nehézség szerint random hosszú szavakat eltárolja egy láncolt listába
 * @param difficulty nehézség változója
 * @param Dictionary A fájl változói, ami tárolj a szavak hosszát és a listát ami feltölt
 * @param dictionary A beolvasandó fájl
 * @return nincs
 * */
static void load_pool(int difficulty, DictionaryVars* Dictionary,FILE* dictionary){
    srand(time(0));
    static char line[450];
    Dictionary->wordpool = NULL;
    Dictionary->no_words=0;
    Dictionary->wordlen=rand()%3+len[difficulty];
    while(fgets(line,sizeof(line),dictionary)){
        if(strlen(line)==Dictionary->wordlen+1){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=(char*)malloc(sizeof(char)*(strlen(line)+1));
            strcpy(new->word,line);
            new->next=Dictionary->wordpool;
            Dictionary->wordpool=new;
            Dictionary->no_words++;
        }
    }
    if(Dictionary->wordpool==NULL){
        perror("nem sikerült feltölteni a listát szavakkal");
    }
}
/**
 * Megnyitja a megfelelő fájlt
 * @param difficulty A játék nehézsége, tovabbadja a láncolt lista betöltéséhez
 * @param lang A játék szavainak nyelve
 * @return szótár változók, ami a szavakat és ezek hosszát tárolja
 * */
DictionaryVars* load_dictionary(int difficulty,int lang){
    DictionaryVars* Dictionary=malloc(sizeof(DictionaryVars));
    FILE* dictionary;
    dictionary = fopen(files[lang],"r"); 
    if(dictionary==NULL){
        perror("Hiba a fájl megnyitása közben");
        return NULL;
    }
    load_pool(difficulty,Dictionary,dictionary);
    fclose(dictionary);
    return Dictionary;
}

/**
 * Felszabadítja a szótár változótit
 * @param dictionary a felszabadítondó változók csoportja
 * @return nincs
 * */
void clear_dictionary(DictionaryVars* dictionary){
    dictionary->no_words=0;
    clear_pool(dictionary);
    free(dictionary);
}
