#ifndef JUMPER_H
#define JUMPER_H

#include "../Player.h"

#include <string>

#include "../types.h"
#include "../Interfaces/player.h"

class JumperPlayer : public Player
{
    unsigned char _color[3] = {0, 0, 255};
public:
    RandomPlayer();
    virtual ~RandomPlayer();

    //Sets up the player to run a specific maze type
    virtual void setMazeSettings(const MazeSettings& settings){}

    //Return a string to be the player's name
    virtual std::string playerName(){return "Random";}

    //Return an unsigned char[3] RGB color array
    virtual unsigned char* playerColor(){return _color;}

    //Main player interface. The game will call getMove and the player will
    //return a direction to move. If it is an invalid direction, they forfeit their
    //move that turn. The pointer is not guaranteed to remain valid after the function
    //returns, so don't try to save it
    virtual PlayerMove move(const MapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y);          //Location in local grid
};
#endif