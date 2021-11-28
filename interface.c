/**
 * @file
 * @section LEÍRÁS
 * A fájl kezeli a kiírásokat, összeköti a programot a felhasználoval
 * */

#include "interface.h"
#include "game.h"
#include "dictionary.h"
#include "debugmalloc.h"
#include "econio.h"

/** 
 * Képernyő törlése, több operációs rendszerre is
 * */
void clear(){
    #ifdef _WIN32
    system("cls");
    #else 
    system("clear");
    #endif
}
/**
* Kiirja, ha rossz a tipp, vagy ha vége a játéknak
* @param game élet csökkentéséhez
* @return nincs
*/
void bad_guess(GameVars* game){
    game->lives--;
    clear();
    printf("Rossz a tipp!\n\n");
    fflush(stdout);
}

/**
* Játék végét felügyelő függvény
* @param GameVars játék vége eldöntéséhez, a helyes szó kiirásához
* @return nincs
*/
bool eo_game(GameVars* game){
    if(game->won){
        printf("A szó %s volt\nGratulálok\n\n*Új játékhoz nyomj meg egy gombot*\n",game->dictionary->wordpool->word);
        fflush(stdout);
        return true;
    }
    else if(game->lives==0){
        printf("Vesztettél\nA szó %s volt\nSok sikert legközelebb\n\n*Új játékhoz nyomj meg egy gombot*\n",game->dictionary->wordpool->word);
        fflush(stdout);
        return true;
    }
    return false;
}

/** Kiirja a menü sávot
* @return nincs
*/
static void write_menu(){
    printf("0) Kilépés (1) Menü\n");
}

/**A játék fő felületét írja ki
* @param game a játék változói, ezek függvényében írja ki a jelenlegi helyzetet
* @return nincs 
*/
static void write_game(GameVars* game){
    printf("Életeid száma: %d\n",game->lives);
    fflush(stdout);
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

/** Bekérdezi a nyelvet amilyen szavakkal a játékos játszani szeretne
* @return visszatér a nyelvet meghatározó számmal
*/
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

/** Bekérdezi a nehézséget amin a játékos játszani szeretne
* @return visszatér a nehézséget meghatározó számmal
*/
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
/** Betölti a játékot a bekért változókkal
* @return a Játék változói
*/
GameVars* initialize(){
    clear();
    int lang=choose_lang();
    int difficulty=choose_difficulty();
    GameVars* game=InitGame(difficulty,lang);
    return game;
}

/**A játék fő loopja, ez ismétlődik
* @return Hamisat ad vissza, ha ki kell lépni a játékból
*/
static bool game_loop(GameVars* game){
    write_menu();
    if(!eo_game(game)){
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

/** Loopolja a játékot, ha vége bezárja a szükséges dolgokat
* @return nincs
*/
void run_game(GameVars* game){
    while(game_loop(game)){
        ;
    }
    CloseGame(game);
    clear();
};