#include <stdio.h>
#include <stdbool.h>

int write_hun(char* kitalalando){
    printf("\r");
}

int write_eng(char* kitalalando){
    printf("\r");
}

void write(bool lang,char* kitalalando){
    if(lang) write_hun(kitalalando);
    else write_eng(kitalalando);

}

int choose_lang(){
    int a;
    printf("Milyen nyelven szeretnél játszani?\n 1-Magyar 0-Angol \n");
    scanf("%d",&a);
    return a;
}