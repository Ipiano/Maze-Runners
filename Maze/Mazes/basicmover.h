#ifndef _BASICMOVER_H
#define _BASICMOVER_H

#include "../types.h"
#include "../Interfaces/playermover.h"
#include "../Interfaces/player.h"

class BasicMover : public PlayerMover<Player>
{
public:
    point movePlayer(const int& playerId,
                     const PlayerMove& move,
                     const maze& m);
};

#endif