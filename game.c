#include "game.h"
#include "interface.h"
#include "time.h"
#include "debugmalloc.h"
#include "econio.h"
#include "math.h"
#include "dictionary.h"
#include "time.h"

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

static char* get_base_clue(GameVars* game){
    srand(time(0));
    int wordlen;
    //szóhossz generálása
    switch(game->difficulty){
        case 1:
            wordlen=4;
            break;
        case 2:
            wordlen=rand()%2+6;
            break;
        case 3:
            wordlen=rand()%5+8;
            break;
    }
    //szólista szűkítése
    Words* temp1=game->dictionary->wordpool;
    for (; temp1->next!=NULL; temp1=temp1->next)
    {
        if(strlen(temp1->next->word)!=wordlen){
            Words* temp=temp1->next;
            temp1->next=temp->next;
            free(temp->word);
            free(temp);
            game->dictionary->no_words--;
        }
    }
    char* word=(char*)calloc((wordlen+1),sizeof(char));
    //alap "rejtett" szó minta _____ forma
    for (int i = 0; i < wordlen; i++)
    {
        if(word[i]='0')
            word[i]='_';
    }
    word[wordlen]='\0';
    Words* first=(Words*)malloc(sizeof(Words)*strlen(word)+1);
    first->word=word;
    first->next=game->dictionary->wordpool;
    game->dictionary->wordpool=first;
    return word;
}

char get_guess(){
    char  temp;
    temp=econio_getch();
    return temp;
}

bool check_guess(char new,DictionaryVars dict){
    bool empty=false;
    for (int i = 0; i < strlen(dict.wordpool->word); i++)
    {
        if (dict.wordpool->word[i]=='_')
        {
            empty=true;
        }else empty = false;
        if(empty) return true;
    }
    
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

char** gen_new_patterns(char* pattern,char guess){
    int empty=0;
    for (int i = 0; i < strlen(pattern); i++)
    {
        empty++;
    }
    char** patterns=(char**)malloc(sizeof(char*)*pow(2,empty));
    for (int i = 0; i < pow(2,empty); i++)
    {
        patterns[i] = (char*)malloc(sizeof(char)*strlen(pattern)+1);
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
        patterns[i][strlen(pattern)]='\0';
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
            }
        }
        return temp;
    }

int get_set_size(Words* wordset){
    int size=0;
    while (wordset!=NULL)
    {
        size++;
        wordset=wordset->next;
    }
    return size;
}

void free_set(Words* wordset){
    Words* temp;
    while(wordset!=NULL){
        temp=wordset;
        wordset=wordset->next;
        free(temp);
    }
}

void delete_guess(Guesses* guess){
    guess->correct--;
    char* temp=guess->correct_guesses;
    guess->correct_guesses=(char*)malloc(sizeof(char)*guess->correct+1);
    strncpy(guess->correct_guesses,temp,guess->correct);
    guess->correct_guesses[guess->correct]='\0';
    free(temp);
}

Words* get_set(GameVars* game,char* pattern,char guess){
    Words* wordset=NULL;
    Words* temp=game->dictionary->wordpool;
    for (int i = 0; temp!=NULL; i++)
    {
        if(pattern_match(pattern,temp->word,guess)){
            Words* tmp=(Words*)malloc(sizeof(Words));
            tmp->word=temp->word;
            temp=temp->next;
            tmp->next=wordset;
            wordset=tmp;
        }else{
            temp=temp->next;
        }
    }
    return wordset;
}

Words* biggest_set(GameVars* game,char guess){ 
    Words* set=NULL;
    char** patterns;
    int currentbig=0;
    patterns=gen_new_patterns(game->current_clue,guess);
    char* final_pattern;
    free(patterns[0]);
    for (int i = 1; i < pow(2,4); i++)
    {
        if(!strcmp(patterns[i],game->current_clue)){
            free(patterns[i]);
        }
        else{
        strcpy(game->dictionary->wordpool->word,patterns[i]);
        if(pattern_match(patterns[i],game->dictionary->wordpool->word,guess)){
            Words* tmp=get_set(game,patterns[i],guess);
            int size=get_set_size(tmp);
            if(size>currentbig){ 
                if(set!=NULL)free_set(set);
                if(currentbig!=0)free(final_pattern);
                currentbig=size;
                set=tmp;
                final_pattern=patterns[i];
            }
            else
            {
                free(patterns[i]);
                free_set(tmp);
            }
        }
        else{
            free(patterns[i]);
        }
        }
    }
    sizeof_set=currentbig;
    if((currentbig<3)){
        delete_guess(game->guesses);
        return game->dictionary->wordpool;
    }
    free(game->current_clue);
    game->current_clue=(char*)malloc(sizeof(char)*(strlen(final_pattern)+1));
    strcpy(game->current_clue,final_pattern);
    free(final_pattern);
    free(patterns);
    free_set(game->dictionary->wordpool);
    game->dictionary->no_words=currentbig;
    return set;
}

void add_guess(char new, GameVars* game){
    if(!isin(new,game)){
        //többi tipp tárolása
        game->guesses->number_of_guesses++;
        char* temp=(char*)malloc((game->guesses->number_of_guesses+1)*sizeof(char));
        if(game->guesses->number_of_guesses>1)strcpy(temp,game->guesses->guesses);
        free(game->guesses->guesses);    
        temp[game->guesses->number_of_guesses-1]=new;
        game->guesses->guesses=temp;;
        game->guesses->guesses[game->guesses->number_of_guesses]='\0';
        if(check_guess(new,*game->dictionary)){
            game->guesses->correct++;
            char* temp=(char*)malloc((game->guesses->correct+1)*sizeof(char));
            //jó tipp tárolása
            if(game->guesses->correct>1)strcpy(temp,game->guesses->correct_guesses);
            free(game->guesses->correct_guesses);    
            temp[game->guesses->correct-1]=new;
            game->guesses->correct_guesses=temp;;
            game->guesses->correct_guesses[game->guesses->correct]='\0';
            game->dictionary->wordpool=biggest_set(game,new);
        }
        else {
            Words* temp=game->dictionary->wordpool;
            for (; temp->next!=NULL; temp->next=temp->next->next)
            {
                for (int i = 0; i < strlen(temp->word); i++)
                {
                    if(new==temp->next->word[i]){
                        printf("\n%s volt a tipped\n",temp->next->word);
                        game->won=true;
                    }
                }
                
            }
            bad_guess(game);
            
        };

    }
}

GameVars* InitGame(int difficulty,int lang){
    GameVars* game=(GameVars*)malloc(sizeof(GameVars));
    game->won=false;
    game->guesses=guessed_foglal();
    game->lang=lang;
    game->difficulty=difficulty;
    game->dictionary=load_dictionary(difficulty,lang);
    game->current_clue=get_base_clue(game);
    return game;
}

void CloseGame(GameVars* game){
    free(game->current_clue);
    guessed_free(game->guesses);
    clear_dictionary(game->dictionary);
    free(game);
}