#ifndef _BASICMOVER_H
#define _BASICMOVER_H

#include "../types.h"
#include "../Interfaces/playermover.h"
#include "../Interfaces/player.h"

#include <unordered_map>

class BasicMover : public PlayerMover<Player>
{
    std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, bool>>> _visited; //Map player to x to y to visited or not
public:
    void registerPlayer(const int& playerId, const Player* player)
    {
        _visited[playerId].clear();
    };

    point movePlayer(const int& playerId,
                     const PlayerMove& move,
                     maze& m);
};

#endif