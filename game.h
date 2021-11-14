#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"


//tippeket tároló struktúra
typedef struct Guesses{
    char* guesses;
    int number_of_guesses;
    char* correct_guesses;
    int correct;
}Guesses;

typedef struct GameVars{
    int difficulty;
    int lang;
    bool won;
    Guesses* guesses;
    char* current_clue;
    DictionaryVars* dictionary;
}GameVars;

//Játék változóinak létrehozása
GameVars* InitGame(int difficulty,int lang);
//Játék változói megszüntetése új játék, kilépés esetére
void CloseGame(GameVars* game);
void add_guess(char new,GameVars* game);

#endif
