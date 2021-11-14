#include "game.h"
#include "interface.h"
#include "time.h"
#include "debugmalloc.h"
#include "econio.h"

#include "dictionary.h"

Guesses* guessed_foglal(){
    Guesses* guesses=(Guesses*)malloc(sizeof(Guesses));
    guesses->number_of_guesses=0;
    guesses->guesses=(char*)malloc(guesses->number_of_guesses*sizeof(char*));
    guesses->correct=0;
    guesses->correct_guesses=(char*)malloc(guesses->correct*sizeof(char*));
    return guesses;
}

void guessed_free(Guesses *guesses){
    free(guesses->correct_guesses);
    free(guesses->guesses);
    free(guesses);
}

static char* gen_clue(GameVars* game, DictionaryVars dict, Guesses guess){
    free(game->current_clue);
    char* word=(char*)calloc((strlen(dict.wordpool->word)+1),sizeof(char));
        for (int i = 0; i < strlen(dict.wordpool->word); i++)
    {
        if(word[i]='0')
            word[i]='_';
    }
    for (int i = 0; i < guess.correct; i++)
    {
        for (int j = 0; j < strlen(dict.wordpool->word); j++)
        {
            if(guess.correct_guesses[i]==dict.wordpool->word[j]){
                word[j]=dict.wordpool->word[j];
            }
        }
        
    }
    if(!(bool)strcmp(dict.wordpool->word,word)){
        game->won=true;
    }
    return word;
}

char get_guess(){
    char  temp;
    temp=econio_getch();
    return temp;
}

bool check_guess(char new,DictionaryVars dict){
    for (int i = 0; i < strlen(dict.wordpool->word); i++)
    {
        if(new==dict.wordpool->word[i]) return true;
    }
    return false;
    
}

static bool isin(char new, GameVars* game){
    for (int i = 0; i < game->guesses->number_of_guesses; i++)
    {
        if(new==game->guesses->guesses[i]){
            return true;
        }
    }
    return false;
    
}

void add_guess(char new, GameVars* game){
    if(!isin(new,game)){
        if(check_guess(new,*game->dictionary)){
            game->guesses->correct++;
            char* temp=(char*)malloc((game->guesses->correct+1)*sizeof(char));
            //jó tipp tárolása
            if(game->guesses->correct>1)strcpy(temp,game->guesses->correct_guesses);
            free(game->guesses->correct_guesses);    
            temp[game->guesses->correct-1]=new;
            game->guesses->correct_guesses=temp;;
            game->guesses->correct_guesses[game->guesses->correct]='\0';
            game->current_clue=gen_clue(game,*game->dictionary,*game->guesses);
        }
        //többi tipp tárolása
        game->guesses->number_of_guesses++;
        char* temp=(char*)malloc((game->guesses->number_of_guesses+1)*sizeof(char));
        if(game->guesses->number_of_guesses>1)strcpy(temp,game->guesses->guesses);
        free(game->guesses->guesses);    
        temp[game->guesses->number_of_guesses-1]=new;
        game->guesses->guesses=temp;;
        game->guesses->guesses[game->guesses->number_of_guesses]='\0';
    }
}

GameVars* InitGame(int difficulty,int lang){
    GameVars* game=(GameVars*)malloc(sizeof(GameVars));
    game->won=false;
    game->guesses=guessed_foglal();
    game->lang=lang;
    game->difficulty=difficulty;
    game->dictionary=load_dictionary(difficulty,lang);
    return game;
}

void CloseGame(GameVars* game){
    free(game->current_clue);
    guessed_free(game->guesses);
    clear_dictionary(game->dictionary);
    free(game);
}