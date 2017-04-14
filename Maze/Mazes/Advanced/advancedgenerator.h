#ifndef _ADVDFS_GEN_H
#define _ADVDFS_GEN_H

#include "../../Interfaces/mazegenerator.h"
#include "../../types.h"
#include "../../attributeTypes.h"
#include "../../Interfaces/backend_types.h"

class AdvancedGenerator : public MazeGenerator<AdvancedMapTile>
{
    AdvancedMapTile* _maze;
    unsigned int _w, _h;
    double _cycles;

    void _connectTiles(const point& a, const point& b);
    AdvancedMapTile& _tile(const point &loc);
    std::vector<point> _getEmptyAdjacent(const point& loc);
public:
    AdvancedGenerator(int width, int height, double percentCycles = 0) : _w(width), _h(height), _cycles(percentCycles){}

    maze<AdvancedMapTile> generateMaze(unsigned int players);

    //Returns whether or not the maze wraps around on the edges
    bool isWrapped(){return false;}
};

#endif