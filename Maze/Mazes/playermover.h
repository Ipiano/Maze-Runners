#ifndef _PLAYERMOVER_H
#define _PLAYERMOVER_H

#include "../types.h"
#include "backend_types.h"

class PlayerMover
{
public:
    
    /*
     * Returns the location a player will be at after attempting to make a move
     *
     * player - Location of player
     * moveDir - Direction of move desired
     * maze - Pointer to maze
     */
    virtual point movePlayer(const point& player,
                     const MapTile::Direction& moveDir,
                     const maze& m) = 0;
};

#endif