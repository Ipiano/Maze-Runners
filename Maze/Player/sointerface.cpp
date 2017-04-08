#include "sointerface.h"
#include "rightHandPlayer.h"

AttributePlayer* createPlayer()
{
    return new AdvRightHandPlayer();
}

void destroyPlayer(AttributePlayer* p)
{
    delete p;
}
