#include "randomPlayer.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

RandomPlayer::RandomPlayer()
{
    srand(time(NULL));
}

RandomPlayer::~RandomPlayer()
{

}

//Main player interface. The game will call getMove and the player will
//return a move. If it is an invalid move, they forfeit their turn
PlayerMove RandomPlayer::move(const MapTile* surroundings,             //Const pointer to local area
                                const uint& area_width, const uint& area_height, //Size of local area
                                const uint& loc_x, const uint& loc_y)            //Location in local grid
{
    static vector<unsigned char> moves;
    moves.clear();

    unsigned char valid = surroundings[loc_y*area_width + loc_x].exits;

    unsigned char dir = 1;
    for(int i=0; i<4; i++, dir <<= 1)
        if((valid & dir) != 0) moves.push_back(dir);

    return PlayerMove((MapTile::Direction)(moves[rand()%moves.size()]));
}
