#include "squarepartitioner.h"
#include <exception>

using namespace std;

MapTile* SquarePartitioner::getMazeSection(unsigned int& width, unsigned int& height,
                            const point& target_loc, point& relative_loc,
                            const maze& m, MapTile* reuse)
{
    if(reuse == nullptr)
    {
        width = height = 11;
        reuse = new MapTile[width*height];
    }
    MapTile* iter = reuse;

    for(int i=0, i_=target_loc.y-height/2; i<height; i++, i_++)
    {
        for(int j=0, j_=target_loc.x-width/2; j<width; j++, j_++)
        {
            try
            {
                *iter = m.at(point{j_, i_});
            }
            catch(exception& ex)
            {
                *iter = MapTile{0};
            }
            iter++;
        }
    }

    relative_loc = point{width/2, height/2};

    return reuse;
}
