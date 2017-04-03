#include "sointerface.h"
#include "jumperPlayer.h"

Player* createPlayer()
{
    return new JumperPlayer();
}

void destroyPlayer(Player* p)
{
    delete p;
}
