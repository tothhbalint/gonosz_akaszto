#ifndef INTERFACE_H
#define INTERFACE_H
#include "game.h"

//függvény a felület ürítésére
void reset();
//A játék alap kiírása, itt kommunikál a program a játékossal
void write(char* kitalalando,guessed *guesses);
//1-es Magyar szótár, 2-es Angol
void choose_lang();

//1-es nehézség: rövid szavak
//2-es nehézség: hosszabb szavak
//3-as nehézség: több szóból álló kifejezések, igék, lehetetlen nehéz normál akasztófa esetén is
void choose_difficulty();

void show_menu();

#endif