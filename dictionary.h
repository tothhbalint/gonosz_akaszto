#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"

extern FILE* dictionary;
extern Words* wordpool;

FILE *load_dictionary(bool lang);

Words* load_pool(int difficulty);

Words* delete_pool();

#endif