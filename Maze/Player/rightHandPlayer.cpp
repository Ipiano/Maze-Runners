#include "rightHandPlayer.h"
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

RightHandPlayer::RightHandPlayer()
{
}

RightHandPlayer::~RightHandPlayer()
{

}

unsigned char RightHandPlayer::leftDir()
{
    return (_currDir >> 1)> 0?_currDir>>1 : 8;
}

unsigned char RightHandPlayer::rightDir()
{
    return (_currDir << 1)<= 8?_currDir<<1 : 1;
}

//Main player interface. The game will call getMove and the player will
//return a direction to move. If it is an invalid direction, they forfeit their
//move that turn
PlayerMove RightHandPlayer::move(const MapTile* surroundings,             //Const pointer to local area
                                const uint& area_width, const uint& area_height, //Size of local area
                                const uint& loc_x, const uint& loc_y)            //Location in local grid
{
    MapTile loc = surroundings[area_width*loc_y + loc_x];

    _currDir = leftDir();
    while((loc.exits & _currDir) == 0)
        _currDir = rightDir();
    return PlayerMove((MapTile::Direction)_currDir);
}
