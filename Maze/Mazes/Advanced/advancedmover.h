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
public:
    void movePlayer(AdvancedPlayerData& playerData,
                     const AdvancedPlayerMove& move,
                     maze<AdvancedMapTile>& m);
};

#endif