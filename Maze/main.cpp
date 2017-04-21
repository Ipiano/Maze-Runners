#include <iostream>

#include "playerloader.h"
#include "Mazes/Advanced/advancedgenerator.h"
#include "Mazes/Advanced/advancedmover.h"
#include "Mazes/Advanced/advancedpartitioner.h"
#include "Mazes/Advanced/advancedrules.h"
#include "mazerunner.h"

using namespace std;

int main(int argc, char *argv[])
{
    AdvancedGenerator mazeGen(400, 400);
    AdvancedMover playerMove;
    AdvancedPartitioner part;
    AdvancedRules rules;
    MazeRunner<AttributePlayer, AdvancedPlayerData, AdvancedPlayerMove, AdvancedMapTile>
    m(&mazeGen, &part, &playerMove, &rules, 400*400*20);
    PlayerLoader<AttributePlayer> g(&m);

    g.loadPlayers("./Players");

    m.setup();

    while(m.tickGame());

    return 0;
}
