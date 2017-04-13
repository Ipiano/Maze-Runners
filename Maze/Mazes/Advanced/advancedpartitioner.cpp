#include "advancedpartitioner.h"
#include <exception>
#include <cmath>

using namespace std;

AdvancedMapTile* AdvancedPartitioner::getMazeSection(unsigned int& width, unsigned int& height,
                            AdvancedPlayerData& player, point& relative_loc,
                            maze<AdvancedMapTile>& m)
{
    int maxSize = std::max(player.mapVisionDist, player.playerVisionDist)*2 + 1;
    int outSize = maxSize*maxSize;

    point target_loc = point{player.x, player.y};
    width = height = maxSize;
    if(_allocated[outSize] == nullptr)
    {
        _allocated[outSize] = new AdvancedMapTile[width*height];
    }

    AdvancedMapTile* outiter = _allocated[outSize];
    auto initer = m.begin();
    unsigned int mwidth = m.width();
    unsigned int mheight = m.height();
    unsigned int w2 = width/2;
    unsigned int h2 = height/2;
    unsigned int y_start = target_loc.y-h2;
    unsigned int x_start = target_loc.x-w2;

    for(uint i=0, i_ = y_start; i<height; i++, i_++)
    {
        int offset = i_*mwidth + (target_loc.x < w2 ? 0 : x_start);
        initer = m.begin() + std::max(offset, 0);

        for(uint j=0, j_ = x_start; j<width; j++, j_++)
        {
            int _i = i-h2;
            int _j = j-w2;
            int ptDist = sqrt(_j*_j+_i*_i);
            if(i_ >= 0 && i_ < mheight && j_ >= 0 && j_ < mwidth)
            {
                //Check if they get the whole tile
                if(ptDist < player.mapVisionDist)
                {
                    *outiter = *initer;
                }
                //Check if they get just the players and there are actually players
                else if(ptDist < player.playerVisionDist && initer->players.size() > 0)
                {
                    *outiter = AdvancedMapTile();
                    outiter->exits = 0;
                    outiter->players = initer->players;
                }
                //They get nothing
                else
                {
                    *outiter = AdvancedMapTile();
                    outiter->exits = 0;
                }
                ++initer;
            }
            else
            {
                *outiter = AdvancedMapTile();
                outiter->exits = 0;
            }

            ++outiter;
        }
    }

    relative_loc = point{width/2, height/2};

    return _allocated[outSize];
}
