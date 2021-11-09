#include "dictionary.h"
#include "interface.h"
#include "string.h"

FILE* dictionary;
Words* wordpool;

static bool loaded;
static char line[255];
size_t len = 0;
ssize_t size;

static Words* load_easy(FILE* dict){
    while(fscanf(dict,"%s\n",line)){
        if(strlen(line)<5){   
            Words* new;
            new = (Words*)malloc(sizeof(Words));
            new->next=wordpool;
            new->word=(char*)malloc(sizeof(char*)*strlen(line));
            new->word=line;
            wordpool=new;
            printf("%s ",wordpool->word);
            strcat(line,"");
        }
}
}
FILE *load_dictionary(bool lang){
    if(!lang){
        dictionary = fopen("szotar/szavak_magyar.txt","r"); 
        if(dictionary==NULL){
            perror("Hiba a fájl megnyitása közben");
            return NULL;
        }
    }
    else{
        dictionary = fopen("szotar/szavak_angol.txt","r"); 
        if(dictionary==NULL){
            perror("Hiba a fájl megnyitása közben");
            return NULL;
        }
    }
    return dictionary;
}

Words* load_pool(int difficulty){
    wordpool = (Words*)malloc(sizeof(Words));
    wordpool = NULL;
    switch (difficulty)
    {
    case 1:
        wordpool=load_easy(dictionary);
        break;
  /*  case 2:
        wordpool=load_medium(dictionary);
        break;
    default:
        wordpool=load_hard(dictionary);
        break;
    }*/
}}

