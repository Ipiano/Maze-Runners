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

    if(move.attemptedMove == Move::NOOP)
    {
        return out;
    }
    else if(move.attemptedMove == Move::MOVETO)
    {
        const MazePoint& target = move.destination;
        if(target.x == 1 && target.y == 0 && (tile & (unsigned char)MapTile::Direction::EAST))
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else if(target.x == -1 && target.y == 0 && (tile & (unsigned char)MapTile::Direction::WEST))
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else if(target.x == 0 && target.y == 1 && (tile & (unsigned char)MapTile::Direction::SOUTH))
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else if(target.x == 0 && target.y == -1 && (tile & (unsigned char)MapTile::Direction::NORTH))
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else if(visited[out.x + target.x][out.y + target.y])
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else
        {
            cout << "Player " << playerId << " tried to MOVETO to invalid location" << endl;
            cout << "Relative: " << target.x << ", " << target.y << endl;
            cout << "Absolute: " << out.x+target.x << ", " << out.y+target.y << endl;
        }
    }
    else
    {
        cout << "Unsupported move by player " << playerId << " : " << (unsigned int)move.attemptedMove << endl;
    }

    return out;
}
