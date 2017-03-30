#ifndef _MAZEPARTITIONER_H
#define _MAZEPARTITIONER_H

#include "../types.h"
#include "backend_types.h"

class MazePartitioner
{
public:
    /*
     *  Returns an array which contains a subsection of a maze
     *
     *  width, height - Dimensions of section returned
     *      these are strictly [out] variables if reuse is a nullptr, else they are [in]
     *      to specify the size of the array pointed to by reuse
     *  target_loc - x, y location that the array returned is 'around'
     *  relative_loc - x, y location of target_loc in the returned section
     *  m - Maze container to get section of
     *  reuse - Pointer to already allocated array. If this is not nullptr, it must be at least
     *      as big as width*height. If this is nullptr, then function will allocate a new array of size width*height
     */
    virtual MapTile* getMazeSection(unsigned int& width, unsigned int& height,
                            const point& target_loc, point& relative_loc,
                            const maze& m, MapTile* reuse = nullptr) = 0;
};

#endif