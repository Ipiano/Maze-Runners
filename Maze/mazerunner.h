#ifndef MAZE_H
#define MAZE_H

#include <unordered_map>
#include <vector>

#include "./Player/player.h"
#include "types.h"
#include "./Mazes/backend_types.h"
#include "./Mazes/mazegenerator.h"
#include "./Mazes/mazepartitioner.h"
#include "./Mazes/playermover.h"

//Facilitates creating a maze and letting players
//take turns moving through it until end conditions are met
//mazes are defined with 0, 0 in the northwest corner
class MazeRunner
{
    MazeGenerator* _gen;
    MazePartitioner* _part;
    PlayerMover* _move;
    maze _m;

    bool _tellD, _tellE;
    
protected:
    uint _turn_no;
    std::unordered_map<Player*, unsigned int> _players;
    std::unordered_map<Player*, MapTile::Direction> _moves;
    std::unordered_map<Player*, MapTile*> _buffers;

public:
    MazeRunner(MazeGenerator* gen, MazePartitioner* part, PlayerMover* move, bool tellDims, bool tellExit);
    ~MazeRunner();

    const maze& getMaze() { return _m; }
    std::unordered_map<Player*, unsigned int>* getPlayerData(){return &_players;}

    void addPlayer(Player* p);
    void removePlayer(Player* p);

    //Gets moves from all players and then
    //executes the moves
    //Returns false when no more moves should happen
    bool tickGame();

    //Generates the maze and puts players into initial positions
    //May be called multiple times, so it should delete anything that
    //it new'ed last time
    void setup();
};

#endif // MAZE_H
