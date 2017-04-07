#include "advancedmover.h"

#include <iostream>

using namespace std;

void AdvancedMover::movePlayer(AdvancedPlayerData& playerData,
                    const AdvancedPlayerMove& move,
                    maze<AdvancedMapTile>& m)
{
    point out = point{playerData.x, playerData.y};
    unsigned char tile = m.at(out).exits;

    std::unordered_map<int, std::unordered_map<int, bool>>& visited = _visited[playerData.id];
    visited[out.x][out.y] = true;

    if(move.attemptedMove == AdvancedPlayerMove::Move::NOOP)
    {
        return;
    }
    else if(move.attemptedMove == AdvancedPlayerMove::Move::MOVETO)
    {
        const MazePoint& target = move.destination;

        if(target.x == 1 && target.y == 0 && (tile & (unsigned char)AdvancedMapTile::Direction::EAST))
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else if(target.x == -1 && target.y == 0 && (tile & (unsigned char)AdvancedMapTile::Direction::WEST))
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else if(target.x == 0 && target.y == 1 && (tile & (unsigned char)AdvancedMapTile::Direction::SOUTH))
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else if(target.x == 0 && target.y == -1 && (tile & (unsigned char)AdvancedMapTile::Direction::NORTH))
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else if(visited[out.x + target.x][out.y + target.y])
        {
            out = point{out.x + target.x, out.y + target.y};
        }
        else
        {
            cout << "Player " << playerData.id << " tried to MOVETO to invalid location" << endl;
            cout << "Relative: " << target.x << ", " << target.y << endl;
            cout << "Absolute: " << out.x+target.x << ", " << out.y+target.y << endl;
        }
    }
    else
    {
        cout << "Unsupported move by player " << playerData.id << " : " << (unsigned int)move.attemptedMove << endl;
    }

    playerData.x = out.x;
    playerData.y = out.y;
}
