#include "interface.h"
#include "game.h"
#include "dictionary.h"
#include "debugmalloc.h"
#include "econio.h"



static void write_menu(){
    econio_clrscr();
    printf("0) Kilépés (1) Menü\n");
}

static void write_game(GameVars* game){
    if(game->guesses->number_of_guesses>0){
        printf("\nEddigi tippjeid:%s",game->guesses->guesses);
    }
    printf("\nA kitalálandó szó:%s\nMi a következő tipped?\n",(game->current_clue));
}


static int choose_lang(){
    int lang;
    printf("Milyen nyelven szeretnél játszani?\n 1-Magyar 2-Angol \n");
    lang=econio_getch()-'0';
    if(lang<1||lang>2){
        econio_clrscr();
        printf("Nullát vagy egyet adj meg!\n\n");
        lang=-1;
        choose_lang();
    }else lang-=1;
    econio_clrscr();
    return lang;
}

static int choose_difficulty(){
    int difficulty;
    printf("Milyen nehézségen szeretnél játszani?\n 1-Könnyű 2-Közepes 3-Nehéz \n");
    difficulty=econio_getch()-'0';
    if(difficulty<1||difficulty>3){
        econio_clrscr();
        printf("1-3 ig adj meg nehézséget!\n\n");
        difficulty=-1;
        choose_difficulty();
    }
    econio_clrscr();
    return difficulty;
}

GameVars* initialize(){
    int lang=choose_lang();
    int difficulty=choose_difficulty();
    GameVars* game=InitGame(difficulty,lang);
    char* a=find_word(game->dictionary);
    game->current_clue=(char*)calloc(strlen(a)+1,sizeof(char));
    for (int i = 0; i < strlen(a); i++)
    {
        game->current_clue[i]='_';
    }
    game->current_clue[strlen(a)]='\0';
    
    return game;
}

static bool game_loop(GameVars* game){
    write_menu();
    if(!game->won){
        write_game(game);
        char ideg=econio_getch();
        switch(ideg){
            case '0': return false;
            //reset game
            case '1':
                CloseGame(game);
                game=initialize();
                break;
            default:
                add_guess(ideg,game);
                break;
        }
    }
    else{
        write_menu();
        printf("%s volt a szo\njatek vege nyertel\n*Új játékhoz nyomj meg egy gombot*\n",game->dictionary->wordpool->word);
        char ideg;
        ideg=econio_getch();
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
    econio_clrscr();
};