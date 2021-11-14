#ifndef INTERFACE_H
#define INTERFACE_H
#include "game.h"

/*
//1-es Magyar szótár, 2-es Angol
int choose_lang();
//1-es nehézség: rövid szavak
//2-es nehézség: hosszabb szavak
//3-as nehézség: több szóból álló kifejezések, igék, lehetetlen nehéz normál akasztófa esetén is
int choose_difficulty();

//Menü kiírása
void write_menu();


//Játék főoldalának kiírása
void write_game(GameVars* game);*/
void run_game(GameVars* game);
//játék alapjait betölti
GameVars* initialize();
#endif