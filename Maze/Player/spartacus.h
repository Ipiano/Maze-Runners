#ifndef JUMPER_H
#define JUMPER_H

#include <string>
#include <stack>
#include <unordered_map>
#include <vector>
#include <queue>

#include "../types.h"
#include "../Interfaces/attributePlayer.h"
#include "../attributeTypes.h"
#include "../Interfaces/player.h"
#include <vector>

class Spartacus : public AttributePlayer
{
    int wallBreaks;
    unsigned char _color[3] = {0, 200, 0};
    std::vector<MazePoint> targetLine;
    std::vector<MazePoint> plannedPath;

    MazePoint location;
    AdvancedPlayerMove lastMove;
    AdvancedMapTile lastTile;
    bool firstTurn;

    std::unordered_map<int, std::unordered_map<int, bool>> deadEnd;
    std::unordered_map<int, std::unordered_map<int, int>> exitDists;
    std::unordered_map<int, std::unordered_map<int, AdvancedMapTile>> world;

public:
    Spartacus(){}
    virtual ~Spartacus(){}

    virtual PlayerAttributes getAttributes(unsigned int points)
    {
        return PlayerAttributes{6,0,0,0,3,0,0,1};
    }

    //Sets up the player to run a specific maze type
    virtual void setMazeSettings(const MazeSettings& settings);

    //Return a string to be the player's name
    virtual std::string playerName(){return "Spartacus";}

    //Return an unsigned char[3] RGB color array
    virtual unsigned char* playerColor(){return _color;}

    void bfsDeadEnds(const MazePoint& start);
    void bfsExit(const MazePoint& start);
    std::vector<MazePoint> checkPathToTargetLine();
    void getValidDirections(const MazePoint& loc, std::vector<MazePoint>& out);
    AdvancedPlayerMove moveOntoExitPath();


    //Main player interface. The game will call getMove and the player will
    //return a direction to move. If it is an invalid direction, they forfeit their
    //move that turn. The pointer is not guaranteed to remain valid after the function
    //returns, so don't try to save it
    virtual AdvancedPlayerMove move(const AdvancedMapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y);          //Location in local grid

    AdvancedPlayerMove bookkeeping(const AdvancedMapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y);          //Location in local grid
};



extern "C" AttributePlayer* createPlayer() {
   return new Spartacus();
}

extern "C" void destroyPlayer(AttributePlayer *p) {
   delete p;
}
#endif
