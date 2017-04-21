#ifndef _ADVANCED_RULES_H
#define _ADVANCED_RULES_H

#include "../../Interfaces/ruleenforcer.h"
#include "../../types.h"
#include "../../attributeTypes.h"
#include "../../Interfaces/attributePlayer.h"
#include "../../Interfaces/backend_types.h"
#include<unordered_map>

class AdvancedRules : public RuleEnforcer<AttributePlayer, AdvancedPlayerData, AdvancedMapTile>
{
    std::unordered_map<AttributePlayer*, unsigned int> _playerIds;
    uint playerCount = 0;

    void fillPlayerDataFromAttributes(PlayerAttributes attrib, AdvancedPlayerData& data);
public:
    bool playerIsDifferent(const AdvancedPlayerData& before, const AdvancedPlayerData& after)
    {
        return (before.x != after.x) || (before.y != after.y);
    }
    MazeSettings getSettings(const maze<AdvancedMapTile>& m);
    AdvancedPlayerData initPlayer(AttributePlayer* player, maze<AdvancedMapTile>& m);
    bool playerGetsTurn(AdvancedPlayerData playerData, const maze<AdvancedMapTile>& m);
    bool playerIsDone(AdvancedPlayerData playerData, const maze<AdvancedMapTile>& m);
};

#endif
