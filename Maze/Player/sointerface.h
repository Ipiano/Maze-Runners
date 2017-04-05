#ifndef SOINTERFACE_H
#define SOINTERFACE_H

#include "../Interfaces/player.h"
#include "../types.h"

extern "C" Player<PlayerMove, MapTile>* createPlayer();

extern "C" void destroyPlayer(Player<PlayerMove, MapTile>* p);

#endif // SOINTERFACE_H
