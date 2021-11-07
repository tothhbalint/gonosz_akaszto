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

typedef struct guessed{
    char* guesses;
    int size;
    int correct_guesses;
}guessed;

int get_abc(bool lang);

FILE *load_dictionary(bool lang);

bool guessed_foglal(guessed *guesses);

void guessed_free(guessed *guesses);


int number_of_choices(FILE *dictionary);

char *find_word(guessed guesses,FILE *dictionary);

char *gen_clue(guessed guesses,FILE *dictionary);

#endif
