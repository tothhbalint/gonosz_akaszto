#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//szavakat tároló láncolt lista
typedef struct Words{
    char* word;
    struct Words* next;
}Words;

typedef struct DictionaryVars{
    //szótárra mutató pointerg
    FILE* dictionary;
    //szavak halmaza
    Words* wordpool;
    int no_words;
}DictionaryVars;



//Szótár fájl megnyitása, szavak beolvasása
DictionaryVars* load_dictionary(int difficulty,int lan);
//láncolt lista felszabadítása
void clear_dictionary(DictionaryVars* Dictionary);
//random szót választ a lehetőségek közül, későbbiekben komplex keresés
char* find_word(DictionaryVars* dict);


#endif