#ifndef _MAZE_RUNNER_BASE
#define _MAZE_RUNNER_BASE

#include "./Interfaces/backend_types.h"
#include "./Interfaces/player.h"
#include "types.h"

#include <unordered_map>

template<class PlayerType, class PlayerDataType, class Tile>
class MazeRunnerAccess
{
public:
    virtual maze<Tile>& getMaze() = 0;
    virtual std::unordered_map<PlayerType*, PlayerDataType>* getPlayerData() = 0;
};

class MazeRunnerBase
{
public:
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