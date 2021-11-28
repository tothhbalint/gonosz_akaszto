#include "dictionary.h"
#include "string.h"
#include "debugmalloc.h"
#include "time.h"

static const int len[3]={4,6,9};

static const char* files[2]={"szotar/szavak_magyar.txt","szotar/szavak_angol.txt"};

static void clear_pool(DictionaryVars* Dictionary){
    Words* temp;
    while(Dictionary->wordpool!=NULL){
        temp = Dictionary->wordpool;
        Dictionary->wordpool=Dictionary->wordpool->next;
        free(temp->word);
        free(temp);
    }
}

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


void clear_dictionary(DictionaryVars* dictionary){
    dictionary->no_words=0;
    clear_pool(dictionary);
    free(dictionary);
}
