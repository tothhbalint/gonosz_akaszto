#include "gallows.c"
#include "player.c"

void reset(){
    system("clear");
}

void write_hun(char* kitalalando,guessed *guesses){
    printf("A kitalálandó szó:%s\nMi a következő tipped?\n",kitalalando);
    for (int i = 0; i < guesses->correct_guesses; i++)
    {
        printf("%c",guesses->guesses[i]);
    }
}

void write_eng(char* kitalalando,guessed *guesses){
    printf("The word to be guessed:%s\nWhat's your next guess?\n",kitalalando);
    for (int i = 0; i < guesses->correct_guesses; i++)
    {
        printf("%c",guesses->guesses[i]);
    }
    
}

void write(bool lang,char* kitalalando,guessed *guesses){
    if(lang) write_hun(kitalalando,guesses);
    else write_eng(kitalalando,guesses);

}

int choose_lang(){
    int a;
    printf("Milyen nyelven szeretnél játszani?\n 1-Magyar 0-Angol \n");
    scanf("%d",&a);
    return a;
}