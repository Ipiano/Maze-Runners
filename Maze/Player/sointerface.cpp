#include "sointerface.h"
#include "jumperPlayer.h"
#include "../types.h"

Player<PlayerMove, MapTile>* createPlayer()
{
    return new JumperPlayer();
}

void destroyPlayer(Player<PlayerMove, MapTile>* p)
{
    delete p;
}
