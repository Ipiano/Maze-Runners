#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../types.h"

template<class PlayerMoveType, class Tile>
class Player
{
public:
    virtual ~Player(){}

    //Sets up the player to run a specific maze type
    virtual void setMazeSettings(const MazeSettings& settings){}

    //Return a string to be the player's name
    virtual std::string playerName() = 0;

    //Return an unsigned char[3] RGB color array
    virtual unsigned char* playerColor() = 0;

    //Main player interface. The game will call getMove and the player will
    //return a direction to move. If it is an invalid direction, they forfeit their
    //move that turn. The pointer is not guaranteed to remain valid after the function
    //returns, so don't try to save it
    virtual PlayerMoveType move(const Tile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y) = 0;          //Location in local grid
};

typedef Player<PlayerMove, MapTile> BasicPlayer;

#endif // PLAYER_H
