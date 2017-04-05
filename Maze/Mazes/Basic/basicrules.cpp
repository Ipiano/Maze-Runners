#include "basicrules.h"

MazeSettings BasicRules::getSettings(const maze<MapTile>& m)
{
    return MazeSettings{m.width(), m.height(), m.wrapped(), m.exit.x, m.exit.y};
}

BasicPlayerData BasicRules::initPlayer(BasicPlayer* player, const maze<MapTile>& m)
{
    if(_playerIds.find(player) != _playerIds.end())
    {
        return BasicPlayerData{m.players[_playerIds[player]].x, m.players[_playerIds[player]].y, _playerIds[player]};
    }

    if(m.players.size() > playerCount+1)
    {
        playerCount++;
        _playerIds[player] = playerCount;
        return BasicPlayerData{m.players[_playerIds[player]].x, m.players[_playerIds[player]].y , playerCount};
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