#ifndef _PLAYERMOVER_H
#define _PLAYERMOVER_H

#include "backend_types.h"

//Playermovers are templated
//to a specific type of player object
template<class PlayerDataType, class PlayerMoveType, class Tile>
class PlayerMover
{
public:
    virtual PlayerMoveType defaultMove() = 0;

    /*
     * Returns the location a player will be at after attempting to make a move
     *
     * playerId which player number to move
     * move - The player's attempted move
     * maze - Pointer to maze
     */
    virtual void movePlayer(PlayerDataType& playerData,
                            const PlayerMoveType& move,
                            maze<Tile>& m) = 0;
};

#endif