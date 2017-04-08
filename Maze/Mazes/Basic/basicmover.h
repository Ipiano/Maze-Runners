#ifndef _BASICMOVER_H
#define _BASICMOVER_H

#include "../../types.h"
#include "../..//Interfaces/backend_types.h"
#include "../../Interfaces/playermover.h"
#include "../../Interfaces/player.h"

#include <unordered_map>

class BasicMover : public PlayerMover<BasicPlayerData, PlayerMove, MapTile>
{
    std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, bool>>> _visited; //Map player to x to y to visited or not
public:
    virtual PlayerMove defaultMove()
    {
        return PlayerMove(MapTile::Direction::NONE);
    }

    void movePlayer(BasicPlayerData& playerData,
                     const PlayerMove& move,
                     maze<MapTile>& m);
};

#endif