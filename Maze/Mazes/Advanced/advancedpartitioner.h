#ifndef _SQUAREPARTITIONER_H
#define _SQUAREPARTITIONER_H

#include "../../types.h"
#include "../../Interfaces/backend_types.h"
#include "../../Interfaces/mazepartitioner.h"
#include "../../attributeTypes.h"

class AdvancedPartitioner : public MazePartitioner<AdvancedPlayerData, AdvancedMapTile>
{
    AdvancedMapTile* reuse = nullptr;
public:
    virtual AdvancedMapTile* getMazeSection(unsigned int& width, unsigned int& height,
                            AdvancedPlayerData& player, point& relative_loc,
                            maze<AdvancedMapTile>& m);
};

#endif