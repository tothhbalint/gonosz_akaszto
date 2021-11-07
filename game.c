#include "game.h"

int difficulty;
int lang;
FILE* dictionary;

int get_abc(bool lang){
    if(lang)return 45;
    else return 27;
}

FILE *load_dictionary(bool lang){
    if(!lang){
        dictionary = fopen("szotar/szavak_magyar.txt","rw"); 
        if(dictionary==NULL){
            perror("Hiba a fájl megnyitása közben");
            return NULL;
        }
    }
    else{
        dictionary = fopen("szotar/szavak_angol.txt","rw"); 
        if(dictionary==NULL){
            perror("Hiba a fájl megnyitása közben");
            return NULL;
        }
    }
    switch (difficulty)
    {
    case 1:
        /* code */
        break;
    case 2:
        break;
    default:
        break;
    }
    return dictionary;
}

bool guessed_foglal(guessed *guesses) {
    guesses->size=get_abc(lang);
    guesses->guesses=(char*)malloc(guesses->size*sizeof(char*));
    return guesses->guesses != NULL;
}

void guessed_free(guessed *guesses){
    free(guesses->guesses);
}


int number_of_choices(FILE *dictionary){
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
    int size=number_of_choices(dictionary)+1;
    char *words[size]; 
    return words[rand()%size];
}

char *gen_clue(guessed guesses,FILE *dictionary){
    char *word=find_word(guesses,dictionary);
    for (int i = 0; i < strlen(word); i++)
    {
        for (int j = 0; j < guesses.size; j++)
        {
            if(guesses.guesses[j]!=word[i]){
                word[i]='_';
            }
        }
        
    }
    
}

