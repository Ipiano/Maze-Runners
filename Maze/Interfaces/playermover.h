#ifndef _PLAYERMOVER_H
#define _PLAYERMOVER_H

#include "../types.h"
#include "backend_types.h"

//Playermovers are templated
//to a specific type of player object
template<class PlayerType>
class PlayerMover
{
public:
    
    /* 
     * Registers a player so that the mover can set up to move them
     *
     * playerId - Number id used to identify the player during moves
     * player - Pointer to player so the mover can get any extra info needed
     */
    virtual void registerPlayer(const int& playerId, const PlayerType* player){};

    /*
     * Returns the location a player will be at after attempting to make a move
     *
     * playerId which player number to move
     * move - The player's attempted move
     * maze - Pointer to maze
     */
    virtual point movePlayer(const int& playerId,
                     const PlayerMove& move,
                     const maze& m) = 0;
};

#endif