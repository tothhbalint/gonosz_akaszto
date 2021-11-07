#include "interface.h"
#include "game.h"


void reset(){
    system("clear");
}
void write(char* kitalalando,guessed *guesses){
    printf("A kitalálandó szó:%s\nMi a következő tipped?\n",kitalalando);
    for (int i = 0; i < guesses->correct_guesses; i++)
    {
        printf("%c",guesses->guesses[i]);
    }
}
void choose_lang(){
    printf("Milyen nyelven szeretnél játszani?\n 1-Magyar 2-Angol \n");
    scanf("%d",&lang);
    if(lang<1||lang>2){
        reset();
        printf("Nullát vagy egyet adj meg!\n\n");
        lang=-1;
        choose_lang();
    }else lang-=1;
    reset();
}

void choose_difficulty(){
    printf("Milyen nehézségen szeretnél játszani?\n 1-Könnyű 2-Közepes 3-Nehéz \n");
    scanf("%d",&difficulty);
    if(difficulty<1||difficulty>3){
        reset();
        printf("1-3 ig adj meg nehézséget!\n\n");
        difficulty=-1;
        choose_difficulty();
    }
    reset();
}

void show_menu(){
    
}