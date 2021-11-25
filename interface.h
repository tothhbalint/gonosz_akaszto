#ifndef INTERFACE_H
#define INTERFACE_H
#include "game.h"


void run_game(GameVars* game);
void bad_guess();
//játék alapjait betölti
GameVars* initialize();
#endif