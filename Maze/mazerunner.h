#ifndef MAZE_H
#define MAZE_H

#include <unordered_map>
#include <cmath>
#include <ctime>
#include <vector>

#include "./Interfaces/player.h"
#include "types.h"
#include "./Interfaces/backend_types.h"
#include "./Interfaces/mazegenerator.h"
#include "./Interfaces/mazepartitioner.h"
#include "./Interfaces/playermover.h"
#include "mazerunnerbase.h"

//Facilitates creating a maze and letting players
//take turns moving through it until end conditions are met
//mazes are defined with 0, 0 in the northwest corner
template<class PlayerType>
class MazeRunner : public MazeRunnerBase
{
    MazeGenerator* _gen;
    MazePartitioner<PlayerType>* _part;
    PlayerMover<PlayerType>* _move;
    maze _m;
    bool _tellD, _tellE;
    unsigned int _seed;

protected:
    uint _turn_no;
    std::unordered_map<Player*, unsigned int> _players;
    std::unordered_map<Player*, PlayerMove> _moves;

public:
    MazeRunner(MazeGenerator* gen, MazePartitioner<PlayerType>* part, PlayerMover<PlayerType>* move, bool tellDims, bool tellExit, unsigned int seed = 0);
    ~MazeRunner();

    maze& getMaze() { return _m; }
    std::unordered_map<Player*, unsigned int>* getPlayerData(){return &_players;}

    void addPlayer(PlayerType* p);
    void removePlayer(PlayerType* p);

    //Gets moves from all players and then
    //executes the moves
    //Returns false when no more moves should happen
    bool tickGame();

    //Generates the maze and puts players into initial positions
    //May be called multiple times, so it should delete anything that
    //it new'ed last time
    void setup();
};



template<class PlayerType>
MazeRunner<PlayerType>::MazeRunner(MazeGenerator* gen, MazePartitioner<PlayerType>* part, PlayerMover<PlayerType>* move, bool tellDims, bool tellExit, unsigned int seed) 
: _gen(gen), _part(part), _move(move), _tellD(tellDims), _tellE(tellExit), _seed(seed)
{

}

template<class PlayerType>
MazeRunner<PlayerType>::~MazeRunner()
{
    _m.destroy();
}

template<class PlayerType>
void MazeRunner<PlayerType>::addPlayer(PlayerType* p)
{
    _players[p] = _m.players.size();
}

template<class PlayerType>
void MazeRunner<PlayerType>::removePlayer(PlayerType* p)
{
    _players.erase(p);
}

template<class PlayerType>
bool MazeRunner<PlayerType>::tickGame()
{
    //std::cout << "Tick maze" << std::endl;
    unsigned int w, h;
    point relative;
    bool moves = false;
    for(auto p : _players)
    {
        //std::cout << "Tick player " << p.first << " : " << p.second << std::endl;
        if(p.second >= _m.players.size())continue;
        
        point& ploc = _m.players[p.second];
        if(ploc == _m.exit)
        {
            continue;
        }

        moves = true;
        MapTile* area = _part->getMazeSection(w, h, p.second, relative, _m);

        //std::cout << w << ", " << h << ", " << relative.x << ", " << relative.y << std::endl;
        //std::cout << (int)area[relative.y * w + relative.x].exits << std::endl;

        _moves[p.first] = p.first->move(area, w, h, relative.x, relative.y);

        //std::cout << p.first << " moved " << (int)_moves[p.first] << std::endl;

        delete[] area;
    }

    if(!moves)
    {
        return false;
    }

    //std::cout << "Moving players" << std::endl;
    for(auto p : _players)
    {
        //std::cout << p.first << " : " << p.second << std::endl;
        if(p.second >= _m.players.size()) continue;

        point& ploc = _m.players[p.second];
        if(ploc == _m.exit)
        {
            continue;
        }
        ploc = _move->movePlayer(p.second, _moves[p.first], _m);

        if(ploc == _m.exit)
            std::cout << "Player " << p.first->playerName() << " finished on turn " << _turn_no << std::endl;
    }

    _turn_no++;
    return true;
}

template<class PlayerType>
void MazeRunner<PlayerType>::setup()
{
    _m.destroy();

    std::cout << "Random seed: " << _seed << std::endl;
    if(_seed == 0)
        srand(time(NULL));
    else
        srand(_seed);

    _turn_no = 0;
    _m = _gen->generateMaze(_players.size());

    MazeSettings set{_tellD?(int)_m.width():-1, _tellD?(int)_m.height():-1, 
                     _gen->isWrapped(),
                     _tellE?(int)_m.exit.x:-1, _tellE?(int)_m.exit.y:-1 };

    int i=0;
    for(auto& p : _players)
    {
        p.first->setMazeSettings(set);
        p.second = i++;

        _move -> registerPlayer(p.second, p.first);
        _part -> registerPlayer(p.second, p.first);
    }
}


#endif // MAZE_H

