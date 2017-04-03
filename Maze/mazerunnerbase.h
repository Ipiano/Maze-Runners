#ifndef _MAZE_RUNNER_BASE
#define _MAZE_RUNNER_BASE

#include "./Interfaces/backend_types.h"
#include "./Interfaces/player.h"
#include "types.h"

#include <unordered_map>

class MazeRunnerBase
{
public:
    virtual const maze& getMaze() = 0;
    virtual std::unordered_map<Player*, unsigned int>* getPlayerData() = 0;

    //Gets moves from all players and then
    //executes the moves
    //Returns false when no more moves should happen
    virtual bool tickGame() = 0;

    //Generates the maze and puts players into initial positions
    //May be called multiple times, so it should delete anything that
    //it new'ed last time
    virtual void setup() = 0;
};

#endif