#include "basicmover.h"

#include <iostream>

using namespace std;

point BasicMover::movePlayer(const int& playerId,
                    const PlayerMove& move,
                    maze& m)
{
    point out = m.players[playerId];
    unsigned char tile = m.at(out).exits;

    std::unordered_map<int, std::unordered_map<int, bool>>& visited = _visited[playerId];
    visited[out.x][out.y] = true;

    if(move.attemptedMove == Move::MOVETO && (tile & (unsigned char)MapTile::Direction::NORTH))
    {
           
    }
    else
    {
        cout << "Unsupported move by player " << playerId << " : " << (unsigned char)move.attemptedMove << endl;
    }

    return out;
}
