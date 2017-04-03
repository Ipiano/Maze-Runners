#ifndef SOINTERFACE_H
#define SOINTERFACE_H

#include "../Interfaces/player.h"

extern "C" Player* createPlayer();

extern "C" void destroyPlayer(Player* p);

#endif // SOINTERFACE_H
