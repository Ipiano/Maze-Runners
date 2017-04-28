#include "lucky.h"

#include <iostream>

using namespace std;

AdvancedPlayerMove LuckyPlayer::move(const AdvancedMapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y)
{
    AdvancedPlayerMove out;

    out.attemptedMove = AdvancedPlayerMove::Move::LUCK;

    return out;
}
