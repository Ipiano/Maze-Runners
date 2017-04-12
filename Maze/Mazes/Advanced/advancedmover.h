#ifndef _ADVANCEDMOVER_H
#define _ADVANCEDMOVER_H

#include "../../types.h"
#include "../..//Interfaces/backend_types.h"
#include "../../Interfaces/playermover.h"
#include "../../attributeTypes.h"

#include <unordered_map>

class AdvancedMover : public PlayerMover<AdvancedPlayerData, AdvancedPlayerMove, AdvancedMapTile>
{
    std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, bool>>> _visited; //Map player to x to y to visited or not

    void performPlayerPendingMove(AdvancedPlayerData& playerData,
                                  maze<AdvancedMapTile>& m);

    void setupNextPlayerMove(AdvancedPlayerData& playerData,
                              const AdvancedPlayerMove& move,
                              maze<AdvancedMapTile>& m);

    bool isValidMove(AdvancedPlayerData& playerData, 
                     const AdvancedPlayerMove& move,
                     maze<AdvancedMapTile>& m);

    int moveLength(AdvancedPlayerData& playerData, 
                    const AdvancedPlayerMove& move,
                    maze<AdvancedMapTile>& m);

    bool adjacentAndConnected(maze<AdvancedMapTile>& m, const uint& x1, const uint& y1, const uint& x2, const uint& y2);

    MazePoint closestPointToExit(MazePoint current, maze<AdvancedMapTile>& m);

public:
    virtual AdvancedPlayerMove defaultMove()
    {
        return AdvancedPlayerMove(AdvancedMapTile::Direction::NONE);
    }

    void movePlayer(AdvancedPlayerData& playerData,
                     const AdvancedPlayerMove& move,
                     maze<AdvancedMapTile>& m);
};

#endif