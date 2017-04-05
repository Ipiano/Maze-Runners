#ifndef _ATTRIB_PLAYER_H
#define _ATTRIB_PLAYER_H

#include "player.h"

class AttributePlayer : public Player
{
public:
    virtual PlayerAttributes getAttributes(unsigned int points) = 0;
};

#endif