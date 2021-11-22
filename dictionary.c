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
        free(temp);
    }
    Dictionary->dictionary=NULL;
}

static void load_easy(DictionaryVars* Dictionary){
    Dictionary->no_words=0;
    Dictionary->wordpool=NULL;
    while(fgets(line,sizeof(line),Dictionary->dictionary)){
        if(strlen(line)<6&&strlen(line)>4){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=strdup(line);
            new->next=Dictionary->wordpool;
            Dictionary->wordpool=new;
            Dictionary->no_words++;
        }
    }
}

static void load_medium(DictionaryVars* Dictionary){
    Dictionary->no_words=0;
    while(fgets(line,sizeof(line),Dictionary->dictionary)){
        if(strlen(line)<8&&strlen(line)>6){
            line[strlen(line)-1]='\0';
            Words* new = (Words*)malloc(sizeof(Words));
            new->word=strdup(line);
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
            new->word=strdup(line);
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



Words* tighten_pool(Words* wordpool,Words* wordset){
    Words* begin=wordpool;
    while(wordset!=NULL){
        while(wordpool!=NULL&&wordpool->word!=wordset->word){
            wordpool=wordpool->next;
        }
        if(wordpool==NULL){
            wordpool=begin->next;
            free(begin);
            wordset=wordset->next;
        }
    }   
}

char* find_word(DictionaryVars* dict){
    srand(time(0));
    Words* temp;
    for (int i = 0; i < rand()%dict->no_words; i++)
    {
        temp=dict->wordpool;
        dict->wordpool=dict->wordpool->next;
        free(temp);
    }
    return dict->wordpool->word;
}

void clear_dictionary(DictionaryVars* dictionary){
    dictionary->no_words=0;
    clear_pool(dictionary);
    if(dictionary->dictionary!=NULL)fclose(dictionary->dictionary);
    free(dictionary);
}
