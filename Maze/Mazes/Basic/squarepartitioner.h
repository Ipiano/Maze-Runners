#ifndef _SQUAREPARTITIONER_H
#define _SQUAREPARTITIONER_H

#include "../../types.h"
#include "../../Interfaces/backend_types.h"
#include "../../Interfaces/mazepartitioner.h"
#include "../../Interfaces/player.h"

class SquarePartitioner : public MazePartitioner<BasicPlayerData, MapTile>
{
    MapTile* reuse = nullptr;
public:
    virtual MapTile* getMazeSection(unsigned int& width, unsigned int& height,
                            BasicPlayerData& player, point& relative_loc,
                            maze<MapTile>& m);
};

#endif