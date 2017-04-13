#include "basicrules.h"
#include <iostream>

using namespace std;

MazeSettings BasicRules::getSettings(const maze<MapTile>& m)
{
    return MazeSettings{m.width(), m.height(), m.wrapped(), m.exit.x, m.exit.y};
}

BasicPlayerData BasicRules::initPlayer(BasicPlayer* player, maze<MapTile>& m)
{
    if(_playerIds.find(player) != _playerIds.end())
    {
        int id = _playerIds[player];
        return BasicPlayerData{m.players[id].x, m.players[id].y, id};
    }

    if(m.players.size() > playerCount)
    {
        int id;
        _playerIds[player] = id = playerCount++;
        return BasicPlayerData{m.players[id].x, m.players[id].y , id};
    }

    return BasicPlayerData{0,0, -1};
    
}

bool BasicRules::playerGetsTurn(BasicPlayerData playerData, const maze<MapTile>& m)
{
    return playerData.id >= 0;
}

bool BasicRules::playerIsDone(BasicPlayerData playerData, const maze<MapTile>& m)
{
    return playerData.x == m.exit.x && playerData.y == m.exit.y;
}