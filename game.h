#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"


//tippeket tároló struktúra
typedef struct Guesses{
    char* guesses; /// a tipplet betűk
    int number_of_guesses; // hány tipp volt
    char* correct_guesses; // jó tippek betűi
    int correct; // hány jó tipp volt
}Guesses;

typedef struct GameVars{
    int difficulty;
    int lang;
    bool lost;  // vesztett-e a játékos
    int lives; // hány élete (tippje van még hátra)
    Guesses* guesses; // a tippek a játék során
    char* current_clue; // megjelenítendő minta
    DictionaryVars* dictionary; // a meg szóba jöhető szavak listája
}GameVars;

//Játék változóinak létrehozása
GameVars* InitGame(int difficulty,int lang);
//Játék változói megszüntetése új játék, kilépés esetére
void CloseGame(GameVars* game);
void add_guess(char new,GameVars* game);
void free_set(Words* set);

#endif
