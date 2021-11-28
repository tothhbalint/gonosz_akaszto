/**
 *@file 
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/**
 * szavakat tároló láncolt lista
*/
typedef struct Words{
    /**szó a listában */
    char* word; 
    /**következő listaelem pointere*/
    struct Words* next; 
}Words;


/**
* Szótár változók
*/
typedef struct DictionaryVars{
    /**szavak listája*/
    Words* wordpool; 
    /**szavak hossza*/
    int wordlen;
    /**szavak száma*/
    int no_words;
}DictionaryVars;

DictionaryVars* load_dictionary(int difficulty,int lan);
void clear_dictionary(DictionaryVars* Dictionary);


#endif