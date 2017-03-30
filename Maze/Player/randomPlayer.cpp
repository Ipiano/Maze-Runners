#include "randomPlayer.h"

#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

RandomPlayer::RandomPlayer()
{
    srand(time(NULL));
}

RandomPlayer::~RandomPlayer()
{

}

//Main player interface. The game will call getMove and the player will
//return a direction to move. If it is an invalid direction, they forfeit their
//move that turn
MapTile::Direction RandomPlayer::move(const MapTile* surroundings,             //Const pointer to local area
                                const uint& area_width, const uint& area_height, //Size of local area
                                const uint& loc_x, const uint& loc_y)            //Location in local grid
{
    MapTile loc = surroundings[loc_y*area_width + loc_x];

    unsigned char dir;
    do
    {
        dir = rand()%5 * 2;
        if(dir == 6) dir = 1;
    }while((dir & loc.exits) == 0);
    return (MapTile::Direction)(dir);
}
