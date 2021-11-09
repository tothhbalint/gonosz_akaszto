#include "interface.h"
#include "game.h"
#include "dictionary.h"


int main(){
    initialize();
    while(game_state());
    printf("NACSÁÁÁÁÁÁÁÁ\n *Nyomd meg a spacet a kilépséhez*\n");
    char exit;
    do{
        scanf("%c",&exit);
    }while(exit!=' ');
    return 0;
}
