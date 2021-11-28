/**
 * @file
 * @section LEÍRÁS
 * A fájl kezeli a játék változóit, a menetét
 * */
#include "game.h"
#include "interface.h"
#include "time.h"
#include "debugmalloc.h"
#include "math.h"

/**
 * standard függvény újraírva kb, hogy debugmallocal használható legyen
 * @param str bemeneti string
 * @param new bégére füzendő karakter
 * @param len új hossz
 * @return az új string
 * */
char* stradd(char* str, char new,int len){
    char* temp=(char*)malloc((len+1)*sizeof(char));
    if(new!='\0'){
        strcpy(temp,str);
        free(str);
        temp[len-2]=new;
        str=temp;;
        str[len-1]='\0';
    }else{
        str=temp;
        temp[len-1]=new;
    }
    return str;
}

/**
 * Lefoglalja a tippek struktúráját
 * @return visszaadja a struktúrát
 * */
Guesses* guessed_alloc(){
    Guesses* guesses=(Guesses*)malloc(sizeof(Guesses));
    guesses->number_of_guesses=0;
    guesses->guesses=stradd(guesses->guesses,'\0',guesses->number_of_guesses+2);
    guesses->correct=0;
    guesses->correct_guesses=stradd(guesses->guesses,'\0',guesses->correct+2);
    return guesses;
}


/**
 * Felszabadítja a tippek struktúráját
 * @return nincs
 * */
void guessed_free(Guesses *guesses){
    free(guesses->correct_guesses);
    free(guesses->guesses);
    free(guesses);
}
/**
 * Létrehoz egy mintát a szavak hossza alapján
 * @param game A játék változói, a szavak hossza miatt
 * @return visszatér a mintával
 * */
static char* get_base_clue(GameVars* game){
    char* word=(char*)calloc((game->dictionary->wordlen+1),sizeof(char));
    //alap "rejtett" szó minta _____ forma
    for (int i = 0; i < game->dictionary->wordlen; i++)
    {
        if(word[i]='0')
            word[i]='_';
    }
    return word;
}

/**
 * Megnézi, hogy a a karakter bennevan bármelyik szóban is
 * @param new karakter amit keresünk
 * @param dict tárolj a listát amiben keresünk
 * @return
 * */
bool check_all_words(char new,DictionaryVars dict){
    bool empty=false;
    for (int i = 0; i < strlen(dict.wordpool->word); i++)
    {
        if (dict.wordpool->word[i]=='_')
        {
            empty=true;
        }else empty = false;
        if(empty) return true;
    }
    for (; dict.wordpool!=NULL; dict.wordpool=dict.wordpool->next)
    {
     if(strchr(dict.wordpool->word,new)!=NULL)return true;
    }
    return false;
}


/**
 * Megkeresi az üres helyeket egy mintában
 * @param str egy minta amiben keresünk helyeket('_')
 * @return hátralévő helyek száma
 * */
int space_left(char* str){
    int left=0;
    for (int i = 0; i < strlen(str); i++)
    {
        if(str[i]=='_')left++;
    }
    return left;
}

/**
 * Létrehozza a lehetséges szó mintákat
 * @param pattern mostani minta, alapból _ * szóhossz  
 * @param guess az új tipp, amivel generáljuk a mintákat
 * @return a minták halmaza
 * */
char** gen_new_patterns(char* pattern,char guess){
    int empty=0;
    empty=space_left(pattern);
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

/**
 * Megnézi, hogy az adott szó illik e a mintára
 * @param pattern minta amihez hasonlítunk
 * @param word szó amit hasonlítunk
 * @param guess jelenlegi tipp
 * @return igaz, ha ráillik, hamis ha nem
 * */
bool pattern_match(char* pattern,char* word,char guess){
        bool temp=false;
        for (int j = 0; j < strlen(word); j++)
        {
            if(pattern[j]!='_'){
                if(pattern[j]==word[j])
                    temp=true;
                else
                    return false;
            }
            else if(word[j]==guess)
                return false;
        }
        return temp;
    }

/**
 * Visszaadja a szavak számát egy listában
 * @param wordset 
 * @return szavak száma
 * */
int get_set_size(Words* wordset){
    int size=0;
    while (wordset!=NULL)
    {
        size++;
        wordset=wordset->next;
    }
    return size;
}

/**
 * Felszabadítja a szavak listáját
 * @param wordset felszabadítandó list
 * @return nincs
 * */
void free_set(Words* wordset){
    Words* temp;
    while(wordset!=NULL){
        temp=wordset;
        wordset=wordset->next;
        free(temp->word);
        free(temp);
    }
}

/**
 * Alhalmazt csinál a szavak halmazából a minta alapján
 * @param game szavak főhalmaza
 * @param pattern minta
 * @param guess jelenlegi tipp
 * @return alhalmaz
 * */
Words* get_set(GameVars* game,char* pattern,char guess){
    Words* wordset=NULL;
    Words* temp=game->dictionary->wordpool;
    for (int i = 0; temp!=NULL; i++)
    {
        if(pattern_match(pattern,temp->word,guess)){
            Words* tmp=(Words*)malloc(sizeof(Words));
            tmp->word=(char*)malloc(sizeof(char)*(strlen(temp->word)+1));
            strcpy(tmp->word,temp->word);
            tmp->word[strlen(temp->word)]='\0';
            temp=temp->next;
            tmp->next=wordset;
            wordset=tmp;
        }else{
            temp=temp->next;
        }
    }
    return wordset;
}

/**
 * Megkeresi a legnagyobb alhalmazt ami megfelel a feltételeknek
 * @param game játék változók
 * @param guess jelenlegi tipp
 * @return legnagyobb alhalmaz
 * */
Words* biggest_set(GameVars* game,char guess){ 
    Words* set=NULL;
    char** patterns;
    int currentbig=0;
    patterns=gen_new_patterns(game->current_clue,guess);
    char* final_pattern;
    for (int i = 0; i < pow(2,space_left(game->current_clue)); i++)
    {
        Words* tmp=get_set(game,patterns[i],guess);
        int size=get_set_size(tmp);
            if(size>currentbig){ 
                if(set!=NULL)free_set(set);
                if(currentbig!=0)free(final_pattern);
                currentbig=size;
                set=tmp;
                final_pattern=patterns[i];
            }
            else{
                free(patterns[i]);
                free_set(tmp);
            }
    }
    if(space_left(final_pattern)==0){
        game->won=true;
        bad_guess(game);
    }
    if(!strcmp(game->current_clue,final_pattern)){
        bad_guess(game);
    }
    game->dictionary->no_words=currentbig;
    free(game->current_clue);
    game->current_clue=(char*)malloc(sizeof(char)*(game->dictionary->wordlen+1));
    strcpy(game->current_clue,final_pattern);
    free(final_pattern);
    free(patterns);
    free_set(game->dictionary->wordpool);
    return set;
}

/** Kiértékel egy tippet, megadja rá a választ.
* @param new a tippelt betü
* @param game a játék
* @return nincs
**/
void add_guess(char new, GameVars* game){
    if(strchr(game->guesses->guesses,new)==NULL){
        //többi tipp tárolása
        game->guesses->number_of_guesses++;
        game->guesses->guesses=stradd(game->guesses->guesses,new,game->guesses->number_of_guesses+1);
        if(check_all_words(new,*game->dictionary)){
            game->guesses->correct++;
            game->guesses->correct_guesses=stradd(game->guesses->correct_guesses,new,game->guesses->correct+1);
            game->dictionary->wordpool=biggest_set(game,new);
        }
        else {
            bad_guess(game);
        }
    }
}

/**
 * Inicializálja a játékot
 * @param difficulty játék nehézsége
 * @param lang játék szavainak nyelve
 * @return játék változói
 * */
GameVars* InitGame(int difficulty,int lang){
    GameVars* game=(GameVars*)malloc(sizeof(GameVars));
    game->won=false;
    game->guesses=guessed_alloc();
    game->lang=lang;
    game->difficulty=difficulty;
    game->lives=22;
    game->dictionary=load_dictionary(difficulty,lang);
    game->current_clue=get_base_clue(game);
    return game;
}

/**
 * Felszabadítja a jelenlegi játékot
 * @param game játékváltozók
 * @return nincs
 * */
void CloseGame(GameVars* game){
    free(game->current_clue);
    guessed_free(game->guesses);
    clear_dictionary(game->dictionary);
    free(game);
}