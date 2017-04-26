#ifndef LUCKY_H
#define LUCKY_H

#include <string>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../types.h"
#include "../Interfaces/attributePlayer.h"
#include "../attributeTypes.h"
#include "../Interfaces/player.h"

class LuckyPlayer : public AttributePlayer
{
    unsigned char _color[3] = {212, 175, 55};

public:
    LuckyPlayer(){}
    virtual ~LuckyPlayer(){}

    virtual PlayerAttributes getAttributes(unsigned int points)
    {
        return PlayerAttributes{0,0,0,10,0,0,0,0};
    }


    //Sets up the player to run a specific maze type
    virtual void setMazeSettings(const MazeSettings& settings)
    {
    }

    //Return a string to be the player's name
    virtual std::string playerName(){return "Lucky";}

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
   return new LuckyPlayer();
}

extern "C" void destroyPlayer(AttributePlayer *p) {
   delete p;
}
#endif
