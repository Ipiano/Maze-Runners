#include "advancedgenerator.h"

#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <cmath>
#include <set>
#include <unordered_map>

using namespace std;

maze<AdvancedMapTile> AdvancedGenerator::generateMaze(unsigned int players)
{
    cerr << "Generating Maze..." << endl;
    
    _maze = new AdvancedMapTile[_w*_h];
    AdvancedMapTile* iter = _maze;

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

    iter = _maze;
    for(uint i=0; i<_h; i++)
    {
        for(uint j=0; j<_w; j++)
        {
            if(rand() % 100 < _cycles)
            {
                iter->exits |= (rand() % 8);

                if(iter->exits & (uint)AdvancedMapTile::Direction::NORTH)
                {
                    if(i>0) (iter-_w)->exits |= (uint)AdvancedMapTile::Direction::SOUTH;
                    else iter->exits &= ~(uint)AdvancedMapTile::Direction::NORTH;
                }

                if(iter->exits & (uint)AdvancedMapTile::Direction::SOUTH)
                {
                    if(i<_h-1) (iter+_w)->exits |= (uint)AdvancedMapTile::Direction::NORTH;
                    else iter->exits &= ~(uint)AdvancedMapTile::Direction::SOUTH;
                }

                if(iter->exits & (uint)AdvancedMapTile::Direction::WEST)
                {
                    if(j>0) (iter-1)->exits |= (uint)AdvancedMapTile::Direction::EAST;
                    else iter->exits &= ~(uint)AdvancedMapTile::Direction::WEST;
                }

                if(iter->exits & (uint)AdvancedMapTile::Direction::EAST)
                {
                    if(j<_w-1) (iter+1)->exits |= (uint)AdvancedMapTile::Direction::WEST;
                    else iter->exits &= ~(uint)AdvancedMapTile::Direction::EAST;
                }
            }

            ++iter;
        }
    }

    maze<AdvancedMapTile> out(_maze, _w, _h, false);

    out.exit = point{rand()%_w, rand()%_h};
    _maze[_w*out.exit.y + out.exit.x].isExit = true;

    unordered_map<uint, unordered_map<uint, bool>> visited;
    vector<queue<point>> startSets;
    vector<queue<point>> smallSets;
    queue<point> front;
    front.push(out.exit);
    visited[out.exit.x][out.exit.y] = true;
    while(front.size())
    {
        if(front.size() >= players)
        {
            //cerr << "Added front size " << front.size() << endl;
            startSets.push_back(front);
        }
        else
            smallSets.push_back(front);

        int frontSize = front.size();
        for(int i=0; i<frontSize; i++)
        {
            point next = front.front();
            front.pop();

            uint curr = out.at(next.x, next.y).exits;
            point add;
            if(curr & (uint)AdvancedMapTile::Direction::NORTH)
            {
                add = point{next.x, next.y-1};
                if(!visited[add.x][add.y])
                {
                    visited[add.x][add.y] = true;
                    front.push(add);
                }
            }

            if(curr & (uint)AdvancedMapTile::Direction::SOUTH)
            {
                add = point{next.x, next.y+1};
                if(!visited[add.x][add.y])
                {
                    visited[add.x][add.y] = true;
                    front.push(add);
                }
            }

            if(curr & (uint)AdvancedMapTile::Direction::EAST)
            {
                add = point{next.x+1, next.y};
                if(!visited[add.x][add.y])
                {
                    visited[add.x][add.y] = true;
                    front.push(add);
                }
            }

            if(curr & (uint)AdvancedMapTile::Direction::WEST)
            {
                add = point{next.x-1, next.y};
                if(!visited[add.x][add.y])
                {
                    visited[add.x][add.y] = true;
                    front.push(add);
                }
            }
        }
    }

    //Pick a random set of starts from the second half of the sets
    //To give some variety
    queue<point> startQ;
    if(startSets.size() > 1)
    {
        startQ = startSets[rand()%(startSets.size()/2) + startSets.size()/2];
    }
    else if(startSets.size() == 1)
    {
        startQ = startSets[0];
    }
    else
    {
        startQ = smallSets.back();
    }

    vector<point> starts;

    //cerr << "Picking player starts from " << startQ.size() << endl;
    while(startQ.size())
    {
        starts.push_back(startQ.front());
        startQ.pop();
    }

    vector<point> list;

    for(uint i=0; i<players; i++)
    {
        if(list.size() == 0) list = starts;
        int startInd = rand()%list.size();
        out.players.push_back(list[startInd]);
        list.erase(list.begin() + startInd);
    }

    cout << "Done!" << endl;

    return out;
}

void AdvancedGenerator::_connectTiles(const point& a, const point& b)
{
    //cerr << a.x << ", " << a.y << " <-> " << b.x << ", " << b.y << endl;
    if(a.x == b.x-1 && a.y == b.y)
    {
        _tile(a).exits |= (unsigned char)AdvancedMapTile::Direction::EAST;
        _tile(b).exits |= (unsigned char)AdvancedMapTile::Direction::WEST;
    }
    else if(a.x == b.x+1 && a.y == b.y)
    {
        _tile(a).exits |= (unsigned char)AdvancedMapTile::Direction::WEST;
        _tile(b).exits |= (unsigned char)AdvancedMapTile::Direction::EAST;
    }
    else if(a.x == b.x && a.y == b.y-1)
    {
        _tile(a).exits |= (unsigned char)AdvancedMapTile::Direction::SOUTH;
        _tile(b).exits |= (unsigned char)AdvancedMapTile::Direction::NORTH;
    }
    else if(a.x == b.x && a.y == b.y+1)
    {
        _tile(a).exits |= (unsigned char)AdvancedMapTile::Direction::NORTH;
        _tile(b).exits |= (unsigned char)AdvancedMapTile::Direction::SOUTH;
    }
}

vector<point> AdvancedGenerator::_getEmptyAdjacent(const point& loc)
{
    vector<point> out;
    if(loc.x > 0 && _tile(point{loc.x - 1, loc.y}).exits == (unsigned char)AdvancedMapTile::Direction::NONE)
        out.push_back(point{loc.x - 1, loc.y});

    if(loc.x + 1 < _w && _tile(point{loc.x + 1, loc.y}).exits == (unsigned char)AdvancedMapTile::Direction::NONE)
        out.push_back(point{loc.x + 1, loc.y});

    if(loc.y > 0 && _tile(point{loc.x, loc.y - 1}).exits == (unsigned char)AdvancedMapTile::Direction::NONE)
        out.push_back(point{loc.x, loc.y - 1});

    if(loc.y + 1 < _h && _tile(point{loc.x, loc.y + 1}).exits == (unsigned char)AdvancedMapTile::Direction::NONE)
        out.push_back(point{loc.x, loc.y + 1});

    return out;
}

AdvancedMapTile& AdvancedGenerator::_tile(const point &loc)
{
    return _maze[loc.y*_w + loc.x];
}
