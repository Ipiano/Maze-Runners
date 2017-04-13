#ifndef _SQUAREPARTITIONER_H
#define _SQUAREPARTITIONER_H

#include "../../types.h"
#include "../../Interfaces/backend_types.h"
#include "../../Interfaces/mazepartitioner.h"
#include "../../attributeTypes.h"
#include <unordered_map>

class AdvancedPartitioner : public MazePartitioner<AdvancedPlayerData, AdvancedMapTile>
{
    std::unordered_map<int, AdvancedMapTile*> _allocated;
    
public:
    ~AdvancedPartitioner()
    {
        for(auto p : _allocated)
            delete[] p.second;
    }
    
    virtual AdvancedMapTile* getMazeSection(unsigned int& width, unsigned int& height,
                            AdvancedPlayerData& player, point& relative_loc,
                            maze<AdvancedMapTile>& m);
};

#endif