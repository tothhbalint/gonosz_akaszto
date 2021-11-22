#include "interface.h"
#include "game.h"
#include "dictionary.h"
#include "econio.h"
#include "debugmalloc.h"
#ifdef _WIN32
#include "Windows.h"
#endif

int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    econio_rawmode();
    
    GameVars* game=initialize();
    
    run_game(game);
    
    printf("\n*Nyomd meg a spacet a kilépéshez*\n");
    
    do{
        if(econio_getch()==' ') break;
    }while(true);

    //econio_clrscr();
    
    return 0;
}
