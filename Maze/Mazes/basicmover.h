#ifndef _BASICMOVER_H
#define _BASICMOVER_H

#include "../types.h"
#include "backend_types.h"
#include "playermover.h"

class BasicMover : public PlayerMover
{
public:

    point movePlayer(const point& player,
                     const MapTile::Direction& moveDir,
                     const maze& m);
};

#endif