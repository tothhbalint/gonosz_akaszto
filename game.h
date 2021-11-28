/**
 * @file
 */

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"


/**tippeket tároló struktúra*/
typedef struct Guesses{
    /** a tippelt betűk*/
    char* guesses; 
    /** hány tipp volt*/
    int number_of_guesses;
     /** jó tippek betűi*/
    char* correct_guesses;
    /** hány jó tipp volt*/
    int correct;
}Guesses;

/**Játék változóit tároló struktúra*/
typedef struct GameVars{
    /** játék nehézsége*/
    int difficulty; 
    /**szavak nyelve*/
    int lang; 
    /**vége van e a játéknak*/
    bool won;
    /**életek száma*/
    int lives; 
    /** a tippek a játék során*/
    Guesses* guesses; 
    /** megjelenítendő minta*/
    char* current_clue; 
    /**a meg szóba jöhető szavak listája*/
    DictionaryVars* dictionary;
}GameVars;

GameVars* InitGame(int difficulty,int lang);
void CloseGame(GameVars* game);
void add_guess(char new,GameVars* game);

#endif
