#ifndef _SQUAREPARTITIONER_H
#define _SQUAREPARTITIONER_H

#include "../types.h"
#include "backend_types.h"
#include "mazepartitioner.h"

class SquarePartitioner : public MazePartitioner
{
public:

    MapTile* getMazeSection(unsigned int& width, unsigned int& height,
                            const point& target_loc, point& relative_loc,
                            const maze& m, MapTile* reuse = nullptr);
};

#endif