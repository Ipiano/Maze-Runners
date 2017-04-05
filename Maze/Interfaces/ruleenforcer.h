#ifndef _RULE_ENFORCER_H
#define _RULE_ENFORCER_H

#include "backend_types.h"
template <class PlayerType, class PlayerDataType, class Tile, class MazeSettingsType>
class RuleEnforcer
{
public:
    virtual MazeSettingsType getSettings(const maze<Tile>& m) = 0;
    virtual PlayerDataType initPlayer(PlayerType* player, const maze<Tile>& m) = 0;
    virtual bool playerGetsTurn(PlayerDataType playerData, const maze<Tile>& m) = 0;
    virtual bool playerIsDone(PlayerDataType playerData, const maze<Tile>& m) = 0;
};

#endif