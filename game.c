#include "game.h"
#include "interface.h"
#include "time.h"
#include "debugmalloc.h"
#include "econio.h"
#include "math.h"
#include "dictionary.h"

static int sizeof_set=0;

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

char** gen_patterns(char guess,int len){
    char** patterns=(char**)malloc(sizeof(char*)*pow(2,len));
    for (int i = 0; i < pow(2,len); i++)
    {            
        patterns[i] = (char*)malloc(sizeof(char)*len);
        int temp = i;
        for (int j = 0; j < len; j++)
        {
            if (temp%2 == 1)
                patterns[i][j] = guess;
            else
                patterns[i][j] = '_';
                temp = temp/2;
        }
    }
    return patterns;
}

char** gen_new_patterns(char* pattern,char guess){
    int empty=0;
    for (int i = 0; i < strlen(pattern); i++)
    {
        empty++;
    }
    char** patterns=(char**)malloc(sizeof(char*)*pow(2,empty));
    for (int i = 0; i < pow(2,empty); i++)
    {
        patterns[i] = (char*)malloc(sizeof(char)*strlen(pattern));
        int temp = i;
        for (int j = 0; j < strlen(pattern); j++)
        {
            if(pattern[j]=='_'){
                if (temp%2 == 1)
                    patterns[i][j] = guess;
                else
                    patterns[i][j] = '_';
                    temp = temp/2;
            }else patterns[i][j]=pattern[j];
        }
    }
    return patterns;
}

bool pattern_match(char* pattern,char* word,char guess){

        bool temp=false;
        for (int j = 0; j < strlen(word); j++)
        {
            if(pattern[j]!='_'){
                if(pattern[j]==word[j])temp=true;
                else{
                    temp=false;
                    break;
                }
            }else if(word[j]==guess){
                temp=false;
                break;}
        }
        if(temp){
            printf("%s ",pattern);
            return temp;
        }
    
}

Words* get_set(Words* wordpool,char* pattern,char guess){
    Words* wordset=NULL;
    for (int i = 0; wordpool!=NULL; i++)
    {
        if(pattern_match(pattern,wordpool->word,guess)){
            Words* tmp=(Words*)malloc(sizeof(Words));
            tmp->word=wordpool->word;
            wordpool=wordpool->next;
            tmp->next=wordset;
            wordset=tmp;
        }
    }
}

int get_set_size(Words* wordset){
    int size=0;
    while (wordset!=NULL)
    {
        size++;
    }
    return size;
    
}

Words* biggest_set(Words* wordpool,char guess,int len){
    Words* set;
    char** patterns=gen_patterns(guess,len);
    for (int i = 0; i < pow(2,len); i++)
    {
        Words* tmp=get_set(wordpool,patterns[i],guess);
        int size=get_set_size(tmp);
        if(size>sizeof_set){ 
            size=sizeof_set;
            set=tmp;
        }else{
            free_set(tmp);
            free(patterns[i]);
        }
    }
    free(patterns);
    return set;
}

void free_set(Words* wordset){
    Words* temp;
    while(wordset!=NULL){
        temp=wordset;
        wordset=wordset->next;
        free(temp);
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