#ifndef RIGHTPLAYER_H
#define RIGHTPLAYER_H

#include <string>

#include "../types.h"
#include "../Interfaces/player.h"
#include "../Interfaces/attributePlayer.h"

class RightHandPlayer : public BasicPlayer
{
    unsigned char _currDir = 1;
    unsigned char _color[3] = {0, 255, 255};
public:
    RightHandPlayer();
    virtual ~RightHandPlayer();

    unsigned char leftDir();
    unsigned char rightDir();

    //Sets up the player to run a specific maze type
    virtual void setMazeSettings(const MazeSettings& settings){}

    //Return a string to be the player's name
    virtual std::string playerName(){return "Righty";}

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



/*************************ADVANCED VERSION (Uses attributes)*********************************/

class AdvRightHandPlayer : public AttributePlayer
{
    unsigned char _currDir = 1;
    unsigned char _color[3] = {255, 255, 0};
    unsigned int _stickies = 4;
public:
    AdvRightHandPlayer();
    virtual ~AdvRightHandPlayer();

    unsigned char leftDir();
    unsigned char rightDir();

    virtual PlayerAttributes getAttributes(unsigned int points)
    {
        return PlayerAttributes{6,0,0,0,0,4,0,0};
    }

    //Sets up the player to run a specific maze type
    virtual void setMazeSettings(const MazeSettings& settings){}

    //Return a string to be the player's name
    virtual std::string playerName(){return "Righty Med";}

    //Return an unsigned char[3] RGB color array
    virtual unsigned char* playerColor(){return _color;}

    //Main player interface. The game will call getMove and the player will
    //return a direction to move. If it is an invalid direction, they forfeit their
    //move that turn. The pointer is not guaranteed to remain valid after the function
    //returns, so don't try to save it
    virtual AdvancedPlayerMove move(const AdvancedMapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y);          //Location in local grid
};

extern "C" AttributePlayer* createPlayer() {
   return new AdvRightHandPlayer();
}

extern "C" void destroyPlayer(AttributePlayer *p) {
   delete p;
}

#endif // PLAYER_H
