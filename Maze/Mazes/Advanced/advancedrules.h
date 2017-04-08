#ifndef _ADVANCED_RULES_H
#define _ADVANCED_RULES_H

#include "../../Interfaces/ruleenforcer.h"
#include "../../types.h"
#include "../../attributeTypes.h"
#include "../../Interfaces/attributePlayer.h"
#include "../../Interfaces/backend_types.h"
#include<unordered_map>

class AdvancedRules : public RuleEnforcer<AttributePlayer, AdvancedPlayerData, AdvancedMapTile, MazeSettings>
{
    std::unordered_map<AttributePlayer*, unsigned int> _playerIds;
    int playerCount = 0;

    void fillPlayerDataFromAttributes(PlayerAttributes attrib, AdvancedPlayerData& data);
public:

    MazeSettings getSettings(const maze<AdvancedMapTile>& m);
    AdvancedPlayerData initPlayer(AttributePlayer* player, const maze<AdvancedMapTile>& m);
    bool playerGetsTurn(AdvancedPlayerData playerData, const maze<AdvancedMapTile>& m);
    bool playerIsDone(AdvancedPlayerData playerData, const maze<AdvancedMapTile>& m);
};

#endif;