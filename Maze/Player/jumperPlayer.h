#ifndef JUMPER_H
#define JUMPER_H

#include <string>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../types.h"
#include "../Interfaces/player.h"

class JumperPlayer : public Player
{
    unsigned char _color[3] = {255, 0, 255};

    std::stack<MazePoint> backtrace;
    std::unordered_map<int, std::unordered_map<int, MapTile>> explored;
    std::unordered_map<int, std::unordered_map<int, bool>> dead;
    std::unordered_map<int, std::unordered_map<int, bool>> visited;
    MazePoint nextLocation, currLocation;
    unsigned int prevUid = 0;

public:
    JumperPlayer();
    virtual ~JumperPlayer();

    void getValidDirections(const MazePoint& loc, vector<MazePoint>& out);
    void bfsDead(const MazePoint& start);

    //Sets up the player to run a specific maze type
    virtual void setMazeSettings(const MazeSettings& settings)
    {
        visited[0][0] = true;
        nextLocation = currLocation = MazePoint{0, 0};

        explored.clear();
        dead.clear();
        visited.clear();
        while(backtrace.size())
            backtrace.pop();
    }

    //Return a string to be the player's name
    virtual std::string playerName(){return "Jumper";}

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