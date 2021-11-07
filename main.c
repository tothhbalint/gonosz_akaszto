#include "interface.h"
#include "game.h"

guessed guesses;

bool init(){
    choose_lang();
    choose_difficulty();
    return guessed_foglal(&guesses);
}

int main(){
    init();
    reset();
    return 0;
}
