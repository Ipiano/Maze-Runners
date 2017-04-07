#ifndef _ATTRIB_PLAYER_H
#define _ATTRIB_PLAYER_H

#include "player.h"
#include "../attributeTypes.h"

class AttributePlayer : public Player<AdvancedPlayerMove, AdvancedMapTile>
{
public:
    virtual PlayerAttributes getAttributes(unsigned int points) = 0;
};

#endif