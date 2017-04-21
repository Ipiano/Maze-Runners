#include "advancedrules.h"
#include <iostream>

using namespace std;

constexpr int ATTRIBUTE_POINTS = 10;

void AdvancedRules::fillPlayerDataFromAttributes(PlayerAttributes attrib, AdvancedPlayerData& data)
{
    //Putting 3 points into speed or intelligence gets 1 bonus in that area
    //and -1 in the other
    data.ticksPerTurn = 5 - attrib.speed/3 + attrib.intelligence/3;
    data.mapVisionDist = 5 + attrib.intelligence/3 - attrib.speed/3;

    data.playerVisionDist = 7 + attrib.sense;
    data.ticksLeftForCurrentMove = 0;
    data.wallBreaksLeft = attrib.strength;
    data.wallPhaseLeft = attrib.mysticality/2;
    data.luckLeft = attrib.luck;
    data.stickyBombAvoids = attrib.agility;
    data.stickyBombs = attrib.cunning;
    data.moveInProgress.attemptedMove = AdvancedPlayerMove::Move::NOOP;
}

MazeSettings AdvancedRules::getSettings(const maze<AdvancedMapTile>& m)
{
    return MazeSettings(m.width(), m.height(), m.wrapped(), m.exit.x, m.exit.y);
}

AdvancedPlayerData AdvancedRules::initPlayer(AttributePlayer* player, maze<AdvancedMapTile>& m)
{
    AdvancedPlayerData out;
    if(_playerIds.find(player) != _playerIds.end())
    {
        int id = _playerIds[player];
        out = AdvancedPlayerData(m.players[id].x, m.players[id].y, id);

    }else if(m.players.size() > playerCount)
    {
        int id;
        _playerIds[player] = id = playerCount++;
        out = AdvancedPlayerData(m.players[id].x, m.players[id].y , id);
    }
    else out = AdvancedPlayerData{0,0, -1};

    if(out.id >= 0)
    {
        m.at(out.x, out.y).players.push_back(out.id);
    }

    PlayerAttributes p = player->getAttributes(ATTRIBUTE_POINTS);

    int attribSum = p.speed+p.intelligence+p.strength+p.luck+p.mysticality+p.cunning+p.sense+p.agility;
    if(attribSum > ATTRIBUTE_POINTS)
    {
        cout << "Player " << out.id << ", " << player->playerName() << ", used too many attribute points! (" << attribSum << ")" << endl;
        p = PlayerAttributes{0,0,0,0,0,0,0};
    }else if(attribSum < ATTRIBUTE_POINTS)
    {
        cout << "Player " << out.id << ", " << player->playerName() << ", did not use all their attribute points! (" << attribSum << ")" << endl;
    }

    fillPlayerDataFromAttributes(p, out);
    MazeSettings set = getSettings(m);
    set.exit_x = m.exit.x - out.x;
    set.exit_y = m.exit.y - out.y;
    player->setMazeSettings(set);

    return out;
}

bool AdvancedRules::playerGetsTurn(AdvancedPlayerData playerData, const maze<AdvancedMapTile>& m)
{
    return playerData.ticksLeftForCurrentMove == 0;
}

bool AdvancedRules::playerIsDone(AdvancedPlayerData playerData, const maze<AdvancedMapTile>& m)
{
    return playerData.x == m.exit.x && playerData.y == m.exit.y;
}
