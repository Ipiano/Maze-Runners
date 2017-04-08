#ifndef _MAZEGENERATOR_H
#define _MAZEGENERATOR_H

#include "backend_types.h"

#include <vector>
#include <utility>

template<class Tile>
class MazeGenerator
{
public:
    /*
     *  Allocates a new maze array and generates a maze
     *
     *  players - Number of players to find starts for
     */
    virtual maze<Tile> generateMaze(unsigned int players) = 0;

    //Returns whether or not the maze wraps around on the edges
    virtual bool isWrapped() = 0;  
};

#endif