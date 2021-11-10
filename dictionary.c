#include "dictionary.h"
#include "string.h"

FILE* dictionary;


Words* wordpool;

static bool loaded;
static char line[100];
int no_words=0;


void clear_pool(){
    Words* temp;

    while(wordpool!=NULL){
        temp = wordpool;
        wordpool=wordpool->next;
        free(temp);
    }
    wordpool=NULL;
}

void load_easy(FILE* dict){
    no_words=0;
    wordpool=NULL;
    while(fgets(line,sizeof(line),dictionary)){
        if(strlen(line)<6&&strlen(line)>4){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=strdup(line);
            new->next=wordpool;
            wordpool=new;
            no_words++;
        }
    }
}

void load_medium(FILE* dict){
    while(fgets(line,sizeof(line),dictionary)){
        if(strlen(line)<8&&strlen(line)>6){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=strdup(line);
            new->next=wordpool;
            wordpool=new;
            no_words++;
        }
    }
}

void load_hard(FILE* dict){
    while(fgets(line,sizeof(line),dictionary)){
        if(strlen(line)>8){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=strdup(line);
            new->next=wordpool;
            wordpool=new;
            no_words++;
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

void load_pool(int difficulty){
    wordpool = (Words*)malloc(sizeof(Words));
    wordpool = NULL;
    switch (difficulty)
    {
    case 1:
        load_easy(dictionary);
        break;
    case 2:
        load_medium(dictionary);
        break;
    default:
        load_hard(dictionary);
        break;
    }
}


