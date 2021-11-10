#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"

//szavakat tároló láncolt lista
typedef struct Words{
    char* word;
    struct Words* next;
}Words;

//szótárra mutató pointer
extern FILE* dictionary;
//szavak halmaza
extern Words* wordpool;

extern int no_words;

//Szótár fájl megnyitása
FILE *load_dictionary(bool lang);

//törli a felületet
void reset();
//nyelv választáshoz
void choose_lang();
//szavak betöltése
void load_pool();
//láncolt lista felszabadítása
void clear_pool();

//szavak betöltése nehézség alapján
static void load_easy();
static void load_medium();
static void load_hard();

#endif