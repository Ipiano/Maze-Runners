#include "advancedrules.h"
#include <iostream>

using namespace std;

MazeSettings AdvancedRules::getSettings(const maze<AdvancedMapTile>& m)
{
    return MazeSettings{m.width(), m.height(), m.wrapped(), m.exit.x, m.exit.y};
}

AdvancedPlayerData AdvancedRules::initPlayer(AttributePlayer* player, const maze<AdvancedMapTile>& m)
{
    if(_playerIds.find(player) != _playerIds.end())
    {
        int id = _playerIds[player];
        return AdvancedPlayerData{m.players[id].x, m.players[id].y, id};
    }

    if(m.players.size() > playerCount)
    {
        int id;
        _playerIds[player] = id = playerCount++;
        return AdvancedPlayerData{m.players[id].x, m.players[id].y , id};
    }

    return AdvancedPlayerData{0,0, -1};
    
}

bool AdvancedRules::playerGetsTurn(AdvancedPlayerData playerData, const maze<AdvancedMapTile>& m)
{
    return playerData.id >= 0;
}

bool AdvancedRules::playerIsDone(AdvancedPlayerData playerData, const maze<AdvancedMapTile>& m)
{
    return playerData.x == m.exit.x && playerData.y == m.exit.y;
}