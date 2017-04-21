#include "basicrules.h"
#include <iostream>

using namespace std;

MazeSettings BasicRules::getSettings(const maze<MapTile>& m)
{
    return MazeSettings(m.width(), m.height(), m.wrapped(), m.exit.x, m.exit.y);
}

BasicPlayerData BasicRules::initPlayer(BasicPlayer* player, maze<MapTile>& m)
{
    BasicPlayerData out;
    if(_playerIds.find(player) != _playerIds.end())
    {
        int id = _playerIds[player];
        out = BasicPlayerData{m.players[id].x, m.players[id].y, id};
    }
    else if(m.players.size() > playerCount)
    {
        int id;
        _playerIds[player] = id = playerCount++;
        out = BasicPlayerData{m.players[id].x, m.players[id].y , id};
    }
    else out = BasicPlayerData{0,0, -1};
    
    MazeSettings set = getSettings(m);
    set.exit_x = m.exit.x - out.x;
    set.exit_y = m.exit.y - out.y;
    player->setMazeSettings(set);

    return out;
}

bool BasicRules::playerGetsTurn(BasicPlayerData playerData, const maze<MapTile>& m)
{
    return playerData.id >= 0;
}

bool BasicRules::playerIsDone(BasicPlayerData playerData, const maze<MapTile>& m)
{
    return playerData.x == m.exit.x && playerData.y == m.exit.y;
}
