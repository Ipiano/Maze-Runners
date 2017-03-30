#ifndef _DFS_GEN_H
#define _DFS_GEN_H

#include "mazegenerator.h"

class DFSGenerator : public MazeGenerator
{
    MapTile* _maze;
    unsigned int _w, _h;

    void _connectTiles(const point& a, const point& b);
    MapTile& _tile(const point &loc);
    std::vector<point> _getEmptyAdjacent(const point& loc);
public:
    DFSGenerator(int width, int height) : _w(width), _h(height){}

    maze generateMaze(unsigned int players);

    //Returns whether or not the maze wraps around on the edges
    bool isWrapped(){return false;}
};

#endif