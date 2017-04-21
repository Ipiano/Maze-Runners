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
#include "./Interfaces/ruleenforcer.h"
#include "./Interfaces/playermover.h"
#include "mazerunnerbase.h"
#include "playergame.h"

#define RUNNER_TEMPLATE template<class PlayerType, class PlayerDataType, class PlayerMoveType, class Tile>
#define RUNNER_TYPE MazeRunner<PlayerType, PlayerDataType, PlayerMoveType, Tile>

//Facilitates creating a maze and letting players
//take turns moving through it until end conditions are met
//mazes are defined with 0, 0 in the northwest corner
RUNNER_TEMPLATE
class MazeRunner : public MazeRunnerBase, public MazeRunnerAccess<PlayerType, PlayerDataType, Tile>, public PlayerGame<PlayerType>
{
    MazeGenerator<Tile>* _gen;
    MazePartitioner<PlayerDataType, Tile>* _part;
    PlayerMover<PlayerDataType, PlayerMoveType, Tile>* _move;
    RuleEnforcer<PlayerType, PlayerDataType, Tile>* _rules;
    
    maze<Tile> _m;
    unsigned int _max_turn;
    unsigned int _seed;

protected:
    uint _turn_no;
    std::unordered_map<PlayerType*, PlayerDataType> _players;
    std::unordered_map<PlayerType*, PlayerMoveType> _moves;

public:
    MazeRunner(MazeGenerator<Tile>* gen, MazePartitioner<PlayerDataType, Tile>* part, PlayerMover<PlayerDataType, PlayerMoveType, Tile>* move, 
               RuleEnforcer<PlayerType, PlayerDataType, Tile>* rules,
               unsigned int max_turns, unsigned int seed = 0);
    ~MazeRunner();

    maze<Tile>& getMaze() { return _m; }
    std::unordered_map<PlayerType*, PlayerDataType>* getPlayerData(){return &_players;}

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

RUNNER_TEMPLATE
RUNNER_TYPE::MazeRunner(MazeGenerator<Tile>* gen, MazePartitioner<PlayerDataType, Tile>* part, PlayerMover<PlayerDataType, PlayerMoveType, Tile>* move, 
               RuleEnforcer<PlayerType, PlayerDataType, Tile>* rules, unsigned int max_turns, unsigned int seed) 
: _gen(gen), _part(part), _move(move), _rules(rules), _max_turn(max_turns), _seed(seed)
{

}

RUNNER_TEMPLATE
RUNNER_TYPE::~MazeRunner()
{
    _m.destroy();
}

RUNNER_TEMPLATE
void RUNNER_TYPE::addPlayer(PlayerType* p)
{
    _players[p] = _rules->initPlayer(p, _m);
}

RUNNER_TEMPLATE
void RUNNER_TYPE::removePlayer(PlayerType* p)
{
    _players.erase(p);
}

RUNNER_TEMPLATE
bool RUNNER_TYPE::tickGame()
{
    //std::cerr << "Game tick" << std::endl;
    bool somePlayerMoved = false;
    int ticks = 0;
    do
    {
        //std::cerr << "Start" << std::endl;
        unsigned int w, h;
        point relative;
        bool moves = false;
        for(auto& p : _players)
        {
           // std::cout << "Get player move: " << p.first << std::endl;
            if(_rules->playerIsDone(p.second, _m)) continue;
            moves = true;

            if(!_rules->playerGetsTurn(p.second, _m))
            {
                //std::cerr << "Player does not get turn" << std::endl;
                _moves[p.first] = _move->defaultMove();
            }
            else
            {
                //std::cerr << "Get section" << std::endl;
                Tile* area = _part->getMazeSection(w, h, p.second, relative, _m);

                //std::cerr << "Get move" << std::endl;
                _moves[p.first] = p.first->move(area, w, h, relative.x, relative.y);
            }
        }

        if(!moves)
        {
            std::cout << "No moves!" << std::endl;
            return false;
        }

        if(_turn_no > _max_turn)
        {
            std::cout << "Players took too long!" << std::endl;
            return false;
        }

        somePlayerMoved = false;
        for(auto& p : _players)
        {
            if(_rules->playerIsDone(p.second, _m)) continue;

            PlayerDataType before = p.second;
            _move->movePlayer(p.second, _moves[p.first], _m);
            somePlayerMoved= somePlayerMoved || _rules->playerIsDifferent(before, p.second);

            if(_rules->playerIsDone(p.second, _m))
                std::cout << "Player " << p.first->playerName() << " finished on turn " << _turn_no << std::endl;
        }

        _turn_no++;
        //std::cerr << "End" << std::endl;
        //std::cerr << "Player moved? " << somePlayerMoved << std::endl;
    }
    while(!somePlayerMoved && ticks++ < 100);
    return true;
}

RUNNER_TEMPLATE
void RUNNER_TYPE::setup()
{
    _m.destroy();

    std::cout << "Random seed: " << _seed << std::endl;
    if(_seed == 0)
        srand(time(NULL));
    else
        srand(_seed);

    _turn_no = 0;
    _m = _gen->generateMaze(_players.size());

    for(auto& p : _players)
    {
        p.second = _rules->initPlayer(p.first, _m);
    }
}

#undef RUNNER_TEMPLATE
#undef RUNNER_TYPE

#endif // MAZE_H

