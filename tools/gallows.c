#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct guessed{
    char* guesses;
    int size;
}guessed;

int get_abc(bool lang){
    if(lang)return 45;
    else return 27;
}

FILE *load_dictionary(bool lang){
    FILE *dicitonary; 
    if(lang)
        dicitonary  = fopen("szotar/magyar_ascii.txt","r");
    else
        dicitonary = fopen("szotar/angol.txt","r");
    return dicitonary;
}

bool guessed_foglal(guessed *guesses,bool lang) {
    guesses->size=get_abc(lang);
    guesses->guesses=(char*)malloc(guesses->size*sizeof(char*));
    return guesses->guesses != NULL;
}

void guessed_free(guessed *guesses){
    free(guesses->guesses);
}


int no_choices(FILE *dictionary){
    int i=0;
    char temp;
    while(!feof(dictionary)){
        temp=fgetc(dictionary);
        if(temp=='\n')i++;
    }
    rewind(dictionary);
    return i;
}

char *find_word(guessed guesses,FILE *dictionary)
{
    int size=no_choices(dictionary)+1;
    char *words[size]; 
    return words[rand()%size];
}

char *gen_clue(guessed guesses,FILE *dictionary){
    char *word=find_word(guesses,dictionary);
    for (int i = 0; i < guesses.size; i++)
    {
        for (int j = 0; j < strlen(word); j++)
        {
            if(guesses.guesses[i]==word[j]){
                word[j]='_';
            }
        }
        
    }
    
}

