#include "interface.h"
#include "game.h"
#include "dictionary.h"
#include "debugmalloc.h"
#include "econio.h"

void clear(){
    #ifdef _WIN32
    system("cls");
    #else 
    system("clear");
    #endif
}

void bad_guess(GameVars* game){
    clear();
    if(!game->won) {
        printf("Rossz a tipp!\n\n");
        fflush(stdout);
    }
    else{
        printf("A szó %s volt\nGratulálok\n\n*Új játékhoz nyomj meg egy gombot*\n",game->dictionary->wordpool->word);
        fflush(stdout);
    }
}

static void write_menu(){
    printf("0) Kilépés (1) Menü\n");
}

static void write_game(GameVars* game){
    if(game->guesses->number_of_guesses>0){
        printf("\nEddigi tippjeid:%s",game->guesses->guesses);
        fflush(stdout);
    }else{
        printf("Sok szerencsét!");
        fflush(stdout);
    }
    printf("\nA kitalálandó szó:%s\nMi a következő tipped?\n",(game->current_clue));
    fflush(stdout);
}


static int choose_lang(){
    int lang=0;
    while(true){
        printf("\nMilyen nyelven szeretnél játszani?\n 1-Magyar 2-Angol \n");
        fflush(stdout);
        fflush(stdin);
        lang=getc(stdin)-'0';
        if(lang==1||lang==2){
            clear();
            return lang-=1;
        }
        else{
            clear();
            printf("Egyet vagy Kettőt adj meg!\n");
            fflush(stdout);
        }
    }
}

static int choose_difficulty(){
    int difficulty;
    while(true){
        printf("Milyen nehézségen szeretnél játszani?\n 1-Könnyű 2-Közepes 3-Nehéz \n");
        fflush(stdout);
        fflush(stdin);
        difficulty=getc(stdin)-'0';
        clear();
        if(difficulty==1||difficulty==2||difficulty==3){
            clear();
            return difficulty-=1;
        }
        else{
            clear();
            printf("1-3 közt add meg a nehézséget");
            fflush(stdout);
        }
    }

}

GameVars* initialize(){
    clear();
    int lang=choose_lang();
    int difficulty=choose_difficulty();
    GameVars* game=InitGame(difficulty,lang);
    return game;
}

static bool game_loop(GameVars* game){
    write_menu();
    if(!game->won){
        write_game(game);
        char ideg=getc(stdin);
        switch(ideg){
            case '0': return false;
            //reset game
            case '1':
                CloseGame(game);
                game=initialize();
                clear();
                break;
            default:
                clear();
                add_guess(ideg,game);
                break;
        }
    }
    else{
        char ideg;
        ideg=getc(stdin);
        switch(ideg){
        case '0': return false;
        //reset game
        default:
            CloseGame(game);
            game=initialize();
            break;
        }
    }
    return true;
}

    
void run_game(GameVars* game){
    while(game_loop(game)){
        ;
    }
    CloseGame(game);
    clear();
};