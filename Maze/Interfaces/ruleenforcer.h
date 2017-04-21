#ifndef _RULE_ENFORCER_H
#define _RULE_ENFORCER_H

#include "backend_types.h"
template <class PlayerType, class PlayerDataType, class Tile>
class RuleEnforcer
{
public:
    virtual bool playerIsDifferent(const PlayerDataType& before, const PlayerDataType& after) = 0;
    virtual PlayerDataType initPlayer(PlayerType* player, maze<Tile>& m) = 0;
    virtual bool playerGetsTurn(PlayerDataType playerData, const maze<Tile>& m) = 0;
    virtual bool playerIsDone(PlayerDataType playerData, const maze<Tile>& m) = 0;
};

#endif