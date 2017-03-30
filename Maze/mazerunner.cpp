#include "mazerunner.h"

#include <iostream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

MazeRunner:: MazeRunner(MazeGenerator* gen, MazePartitioner* part, PlayerMover* move, bool tellDims, bool tellExit) 
: _gen(gen), _part(part), _move(move), _tellD(tellDims), _tellE(tellExit)
{

}

MazeRunner::~MazeRunner()
{
    _m.destroy();
}

void MazeRunner::addPlayer(Player* p)
{
    _players[p] = _m.players.size();
}

void MazeRunner::removePlayer(Player* p)
{
    _players.erase(p);
}

bool MazeRunner::tickGame()
{
    //cout << "Tick maze" << endl;
    unsigned int w, h;
    point relative;
    bool moves = false;
    for(auto p : _players)
    {
        //cout << "Tick player " << p.first << " : " << p.second << endl;
        if(p.second >= _m.players.size())continue;
        
        point& ploc = _m.players[p.second];
        if(ploc == _m.exit)
        {
            continue;
        }

        moves = true;
        MapTile* area = _part->getMazeSection(w, h, ploc, relative, _m);

        //cout << w << ", " << h << ", " << relative.x << ", " << relative.y << endl;
        //cout << (int)area[relative.y * w + relative.x].exits << endl;

        _moves[p.first] = p.first->move(area, w, h, relative.x, relative.y);

        //cout << p.first << " moved " << (int)_moves[p.first] << endl;

        delete[] area;
    }

    if(!moves)
    {
        cout << "No moves" << endl;
        return false;
    }

    //cout << "Moving players" << endl;
    for(auto p : _players)
    {
        //cout << p.first << " : " << p.second << endl;
        if(p.second >= _m.players.size()) continue;

        point& ploc = _m.players[p.second];
        if(ploc == _m.exit)
        {
            continue;
        }
        ploc = _move->movePlayer(ploc, _moves[p.first], _m);

        if(ploc == _m.exit)
            cout << "Player " << p.first->playerName() << " finished on turn " << _turn_no << endl;
    }

    _turn_no++;
    return true;
}

void MazeRunner::setup()
{
    _m.destroy();

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
    }
}
