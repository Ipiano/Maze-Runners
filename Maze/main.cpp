#include <iostream>

#include "playerloader.h"
#include "Mazes/dfsgenerator.h"
#include "Mazes/basicmover.h"
#include "Mazes/squarepartitioner.h"
#include "mazerunner.h"

using namespace std;

int main(int argc, char *argv[])
{
    DFSGenerator mazeGen(400, 400);
    BasicMover playerMove;
    SquarePartitioner part;
    MazeRunner<Player> m(&mazeGen, &part, &playerMove, true, true);
    PlayerLoader<Player> g(&m);

    g.loadPlayers("./Players");

    m.setup();

    while(m.tickGame());

    return 0;
}
