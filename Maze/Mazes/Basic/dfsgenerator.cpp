#include "dfsgenerator.h"

#include <stack>
#include <vector>
#include <iostream>
#include <cmath>
#include <set>

using namespace std;

maze<MapTile> DFSGenerator::generateMaze(unsigned int players)
{
    cerr << "Generating Maze..." << endl;
    
    _maze = new MapTile[_w*_h];
    MapTile* iter = _maze;

    //Assign random uids to the maze tiles
    set<unsigned int> used;
    for(uint i=0; i<_w*_h; i++)
    {
        unsigned int id;
        do
        {
            id = rand();
        }while(used.insert(id).second == false);
        iter->uid = id;

        (iter++)->exits = 0;
    }

    //Non-recursive so the stack is on the heap, allowing bigger maze
    stack<point> retrace;
    retrace.push(point{0,0});
    while(retrace.size())
    {
        point& curr = retrace.top();
        vector<point> dirs = _getEmptyAdjacent(curr);
        if(dirs.size() == 0)
        {
            //cerr << curr.x << ", " << curr.y << " ->" << endl;
            retrace.pop();
        }
        else
        {
            uint choice = rand()%dirs.size();
            retrace.push(dirs[choice]);
            //cerr << dirs[choice].x << ", " << dirs[choice].y << " <-" << endl;
            _connectTiles(curr, dirs[choice]);
        }
    }
    cerr << "Done!" << endl;

    maze<MapTile> out(_maze, _w, _h, false);
    for(uint i=0; i<players; i++)
        out.players.push_back(point{0, 0});
    out.exit = point{rand()%_w, rand()%_h};
    _maze[_w*out.exit.y + out.exit.x].isExit = true;

    return out;
}

void DFSGenerator::_connectTiles(const point& a, const point& b)
{
    //cerr << a.x << ", " << a.y << " <-> " << b.x << ", " << b.y << endl;
    if(a.x == b.x-1 && a.y == b.y)
    {
        _tile(a).exits |= (unsigned char)MapTile::Direction::EAST;
        _tile(b).exits |= (unsigned char)MapTile::Direction::WEST;
    }
    else if(a.x == b.x+1 && a.y == b.y)
    {
        _tile(a).exits |= (unsigned char)MapTile::Direction::WEST;
        _tile(b).exits |= (unsigned char)MapTile::Direction::EAST;
    }
    else if(a.x == b.x && a.y == b.y-1)
    {
        _tile(a).exits |= (unsigned char)MapTile::Direction::SOUTH;
        _tile(b).exits |= (unsigned char)MapTile::Direction::NORTH;
    }
    else if(a.x == b.x && a.y == b.y+1)
    {
        _tile(a).exits |= (unsigned char)MapTile::Direction::NORTH;
        _tile(b).exits |= (unsigned char)MapTile::Direction::SOUTH;
    }
}

vector<point> DFSGenerator::_getEmptyAdjacent(const point& loc)
{
    vector<point> out;
    if(loc.x > 0 && _tile(point{loc.x - 1, loc.y}).exits == (unsigned char)MapTile::Direction::NONE)
        out.push_back(point{loc.x - 1, loc.y});

    if(loc.x + 1 < _w && _tile(point{loc.x + 1, loc.y}).exits == (unsigned char)MapTile::Direction::NONE)
        out.push_back(point{loc.x + 1, loc.y});

    if(loc.y > 0 && _tile(point{loc.x, loc.y - 1}).exits == (unsigned char)MapTile::Direction::NONE)
        out.push_back(point{loc.x, loc.y - 1});

    if(loc.y + 1 < _h && _tile(point{loc.x, loc.y + 1}).exits == (unsigned char)MapTile::Direction::NONE)
        out.push_back(point{loc.x, loc.y + 1});

    return out;
}

MapTile& DFSGenerator::_tile(const point &loc)
{
    return _maze[loc.y*_w + loc.x];
}
