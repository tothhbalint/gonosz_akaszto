#include "game.h"
#include "dictionary.h"
#include "interface.h"

int difficulty;
int lang;

guessed* guesses;

int get_abc(bool lang){
    if(lang)return 45;
    else return 27;
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

char get_guess(){
    char  temp;
    scanf("%c",&temp);
    return temp;
}

void initialize(){
    reset(),
    choose_lang();
    choose_difficulty();
    load_dictionary(lang);
    load_pool(difficulty);
}

bool game_state(){
    write_menu();
    write_game("kurva anyád",guesses);
    switch(get_guess()){
        case '0': return false;
        case '1':
            cleanup();
            initialize();
            break;
        default:
            return true;
    }
}

void cleanup(){
    clear_pool();
    fclose(dictionary);
}