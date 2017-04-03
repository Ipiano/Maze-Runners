#include "basicmover.h"

#include <iostream>

using namespace std;

point BasicMover::movePlayer(const int& playerId,
                    const PlayerMove& move,
                    const maze& m)
{
    point out = m.players[playerId];
    unsigned char tile = m.at(out).exits;

    if(move.attemptedMove == Move::NORTH && (tile & (unsigned char)MapTile::Direction::NORTH))
    {
            out.y--;
            if(out.y < 0) out.y = m.height()-1;
    }
    else if(move.attemptedMove == Move::SOUTH && (tile & (unsigned char)MapTile::Direction::SOUTH))
    {
            out.y = (out.y+1)%m.height();
    }
    else if(move.attemptedMove == Move::WEST && (tile & (unsigned char)MapTile::Direction::WEST))
    {
            out.x--;
            if(out.x < 0) out.x = m.width()-1;
    }
    else if(move.attemptedMove == Move::EAST && (tile & (unsigned char)MapTile::Direction::EAST))
    {
            out.x = (out.x+1)%m.width();
    }
    else
    {
            cout << "Unsupported move by player " << playerId << " : " << (unsigned char)move.attemptedMove << endl;
    }

    return out;
}
