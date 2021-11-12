#include "game.h"
#include "dictionary.h"
#include "interface.h"
#include "time.h"
#include "debugmalloc.h"

int difficulty;
int lang;

bool won=false;

guessed guesses;

bool guessed_foglal(guessed *guesses) {
    guesses->correct_guesses=0;
    guesses->guesses=(char*)malloc(guesses->correct_guesses*sizeof(char*));
    return guesses->guesses != NULL;
}

void guessed_free(guessed *guesses){
    free(guesses->guesses);
}

char* gen_clue(){
    char* word=(char*)calloc((strlen(wordpool->word)+1),sizeof(char));
        for (int i = 0; i < strlen(wordpool->word); i++)
    {
        if(word[i]='0')
            word[i]='_';
    }
    for (int i = 0; i < guesses.correct_guesses; i++)
    {
        for (int j = 0; j < strlen(wordpool->word); j++)
        {
            if(guesses.guesses[i]==wordpool->word[j]){
                word[j]=wordpool->word[j];
            }
        }
        
    }
    if(!(bool)strcmp(wordpool->word,word)){
        won=true;
    }
    return word;
}

char* find_word(){
    srand(time(0));
    Words* temp;
    for (int i = 0; i < rand()%no_words; i++)
    {
        temp=wordpool;
        wordpool=wordpool->next;
        free(temp);
    }
    return wordpool->word;
}

char get_guess(){
    char  temp;
    scanf("%c",&temp);
    if(temp=='\n')temp=get_guess();
    return temp;
}

bool check_guess(char new){
    for (int i = 0; i < strlen(wordpool->word); i++)
    {
        if(new==wordpool->word[i]) return true;
    }
    return false;
    
}

void add_guess(guessed* guesses,char new){
        if(check_guess(new)){
            guesses->correct_guesses++;
            char* temp=(char*)malloc((guesses->correct_guesses+1)*sizeof(char));
            if(guesses->correct_guesses>1)strcpy(temp,guesses->guesses);
            free(guesses->guesses);    
            temp[guesses->correct_guesses-1]=new;
            guesses->guesses=temp;
            guesses->guesses[guesses->correct_guesses]='\0';
    }
}

void initialize(){
    won=false;
    reset(),
    choose_lang();
    choose_difficulty();
    guessed_foglal(&guesses);
    load_dictionary(lang);
    load_pool(difficulty);
    find_word();
}

bool game_state(){
    write_menu();
    if(!won){
        write_game(gen_clue());
        char ideg=get_guess();
        switch(ideg){
            case '0': return false;
            case '1':
                cleanup();
                initialize();
                break;
            default:
                add_guess(&guesses,ideg);
                break;
        }
    }
    else{
        printf("%s volt a szo\njatek vege nyertel\nakarsz ujra jatszani?\n",wordpool->word);
        char ideg;
        scanf("%c",&ideg);
        switch(ideg){
            case '0': return false;
            default:
                cleanup();
                initialize();
                break;
        }
    } 
    return true;
}

void cleanup(){
    clear_pool();
    no_words=0;
    fclose(dictionary);
    guessed_free(&guesses);
}