#include "basicmover.h"

point BasicMover::movePlayer(const point& player,
                    const MapTile::Direction& moveDir,
                    const maze& m)
{
    if((m.at(player).exits & (unsigned char)moveDir) == 0)
        return player;

    point out = player;
    switch(moveDir)
    {
        case MapTile::Direction::NORTH:
            out.y--;
            if(out.y < 0) out.y = m.height()-1;
            break;
        case MapTile::Direction::SOUTH:
            out.y = (out.y+1)%m.height();
            break;
        case MapTile::Direction::WEST:
            out.x--;
            if(out.x < 0) out.x = m.width()-1;
            break;
        case MapTile::Direction::EAST:
            out.x = (out.x+1)%m.width();
            break;
    }

    return out;
}
