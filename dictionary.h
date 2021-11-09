#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"


typedef struct Words{
    char* word;
    struct Words* next;
}Words;

extern FILE* dictionary;
extern Words* wordpool;

void reset();
void choose_lang();
void load_pool();
void clear_pool();

static void load_easy();
static void load_medium();
static void load_hard();

#endif