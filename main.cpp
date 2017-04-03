#include <iostream>

#include "GlutInputSignaler.h"
#include "GlutScreenCanvas.h"
#include "StaticLayout.h"
#include "ScreenHandler.h"

#include "Maze/Mazes/basicmover.h"
#include "Maze/Mazes/dfsgenerator.h"
#include "Maze/mazerunner.h"
#include "Maze/Mazes/squarepartitioner.h"

#include "mazevisualizer.h"
#include "animatedmaze.h"
#include "./Maze/playerloader.h"

using namespace std;

int main(int argc, char** argv)
{
    int width = 100, height = 100, seed = 0;
    if(argc > 2)
    {
        width = stoi(argv[1]);
        height = stoi(argv[2]);
    }

    if(argc > 3)
        seed = stoi(argv[3]);

    GlutInputSignaler input;
    GlutScreenCanvas canvas;

    canvas.init(argc, argv, "Maze", 520, 520);
    input.setAsActiveHandler();

    DFSGenerator mazeGen(width, height);
    BasicMover playerMove;
    SquarePartitioner part;
    MazeRunner<Player> m(&mazeGen, &part, &playerMove, true, true, seed);
    PlayerLoader<Player> g(&m);

    g.loadPlayers("./Players");

    MazeVisualizer visual(&m);
    AnimatedMaze animator(&m);
    animator.reset();

    ScreenHandler screen(&canvas, &input, &visual);

    input.addIdleReceiver(&animator, &AnimatedMaze::tick);
    input.addIdleReceiver(&glutPostRedisplay);

    glutMainLoop();

    input.removeActiveHandler();
    animator.stop();

    return 0;
}
