#include <iostream>

#include "playerloader.h"
#include "Mazes/Basic/dfsgenerator.h"
#include "Mazes/Basic/basicmover.h"
#include "Mazes/Basic/squarepartitioner.h"
#include "Mazes/Basic/basicrules.h"
#include "mazerunner.h"

using namespace std;

int main(int argc, char *argv[])
{
    DFSGenerator mazeGen(400, 400);
    BasicMover playerMove;
    SquarePartitioner part;
    BasicRules rules;
    MazeRunner<BasicPlayer, BasicPlayerData, PlayerMove, MapTile, MazeSettings> m(&mazeGen, &part, &playerMove, &rules, true, true);
    PlayerLoader<BasicPlayer> g(&m);

    g.loadPlayers("./Players");

    m.setup();

    while(m.tickGame());

    return 0;
}
