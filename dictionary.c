#include "dictionary.h"
#include "string.h"
#include "debugmalloc.h"
#include "time.h"


static char line[450];


static void clear_pool(DictionaryVars* Dictionary){
    Words* temp;

    while(Dictionary->wordpool!=NULL){
        temp = Dictionary->wordpool;
        Dictionary->wordpool=Dictionary->wordpool->next;
        free(temp->word);
        free(temp);
    }
    Dictionary->dictionary=NULL;
}

static void load_easy(DictionaryVars* Dictionary){
    Dictionary->no_words=0;
    Dictionary->wordpool=NULL;
    while(fgets(line,sizeof(line),Dictionary->dictionary)){
        if(strlen(line)<7&&strlen(line)>4){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=(char*)malloc(sizeof(char)*(strlen(line)+1));
            strcpy(new->word,line);
            new->next=Dictionary->wordpool;
            Dictionary->wordpool=new;
            Dictionary->no_words++;
        }
    }
}

static void load_medium(DictionaryVars* Dictionary){
    Dictionary->no_words=0;
    while(fgets(line,sizeof(line),Dictionary->dictionary)){
        if(strlen(line)<10&&strlen(line)>7){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=(char*)malloc(sizeof(char)*(strlen(line)+1));
            strcpy(new->word,line);
            new->next=Dictionary->wordpool;
            Dictionary->wordpool=new;
            Dictionary->no_words++;
        }
    }
}

static void load_hard(DictionaryVars* Dictionary){
    Dictionary->no_words=0;
    while(fgets(line,sizeof(line),Dictionary->dictionary)){
        if(strlen(line)>8){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=(char*)malloc(sizeof(char)*(strlen(line)+1));
            strcpy(new->word,line);
            new->next=Dictionary->wordpool;
            Dictionary->wordpool=new;
            Dictionary->no_words++;
        }
    }
}


static void load_pool(int difficulty, DictionaryVars* Dictionary){
    Dictionary->wordpool = NULL;
    switch (difficulty)
    {
    case 1:
        load_easy(Dictionary);
        break;
    case 2:
        load_medium(Dictionary);
        break;
    default:
        load_hard(Dictionary);
        break;
    }
}

DictionaryVars* load_dictionary(int difficulty,int lang){
    DictionaryVars* Dictionary=malloc(sizeof(DictionaryVars));
    if(!(bool)lang){
        Dictionary->dictionary = fopen("szotar/szavak_magyar.txt","r"); 
        if(Dictionary->dictionary==NULL){
            perror("Hiba a fájl megnyitása közben");
            return NULL;
        }
    }
    else{
        Dictionary->dictionary = fopen("szotar/szavak_angol.txt","r"); 
        if(Dictionary->dictionary==NULL){
            perror("Hiba a fájl megnyitása közben");
            return NULL;
        }
    }
    load_pool(difficulty,Dictionary);
    fclose(Dictionary->dictionary);
    return Dictionary;
}


void clear_dictionary(DictionaryVars* dictionary){
    dictionary->no_words=0;
    clear_pool(dictionary);
    if(dictionary->dictionary!=NULL)fclose(dictionary->dictionary);
    free(dictionary);
}
