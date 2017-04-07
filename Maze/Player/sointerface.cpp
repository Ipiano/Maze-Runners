#include "sointerface.h"
#include "randomPlayer.h"

AttributePlayer* createPlayer()
{
    return new AdvRandomPlayer();
}

void destroyPlayer(AttributePlayer* p)
{
    delete p;
}
