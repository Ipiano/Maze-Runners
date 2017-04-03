#ifndef _SQUAREPARTITIONER_H
#define _SQUAREPARTITIONER_H

#include "../types.h"
#include "../Interfaces/mazepartitioner.h"
#include "../Interfaces/player.h"

class SquarePartitioner : public MazePartitioner<Player>
{
public:

    virtual MapTile* getMazeSection(unsigned int& width, unsigned int& height,
                            const unsigned int& player, point& relative_loc,
                            const maze& m, MapTile* reuse = nullptr);
};

#endif