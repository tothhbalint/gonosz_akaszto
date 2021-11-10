#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define split " :";

extern int difficulty;
extern int lang;
extern FILE* dictionary;

//tippeket tároló struktúra
typedef struct guessed{
    char* guesses;
    int correct_guesses;
}guessed;

extern guessed guesses;

extern bool won;

//helyet foglal a tipp struktúrának
bool guessed_foglal(guessed *guesses);

//felszabadítja a tipp struktúrát
void guessed_free(guessed *guesses);

//visszaadja a választható szavak számát
//int number_of_choices();

//random szavat választ a lehetőségek közül
char *find_word();

void add_guess(guessed* guesses,char new);

//tippek alapján megadja a tippet (_ _ a _ _ formátumban)
char *gen_clue();

//játék alapjait betölti
void initialize();

//játékállapotot kezeli (menü, főrész kiirása közti váltogatás)
bool game_state();

//felszabadítja a foglalat területeket
void cleanup();

#endif
