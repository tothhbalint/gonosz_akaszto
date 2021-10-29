#include "tools/interface.h"

typedef int Lang;

guessed guesses;

bool init(guessed guesses,Lang lang){
    return guessed_foglal(&guesses,lang);
}

int main(){
    Lang lang=choose_lang();
    init(guesses,lang);
    reset();
    return 0;
}