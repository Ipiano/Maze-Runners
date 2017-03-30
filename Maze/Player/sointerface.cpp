#include "sointerface.h"
#include "rightHandPlayer.h"

Player* createPlayer()
{
    return new RightHandPlayer();
}

void destroyPlayer(Player* p)
{
    delete p;
}
