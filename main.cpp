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

using namespace std;

int main(int argc, char** argv)
{
    GlutInputSignaler input;
    GlutScreenCanvas canvas;

    canvas.init(argc, argv, "Maze", 520, 520);
    input.setAsActiveHandler();

    DFSGenerator mazeGen(100, 100);
    BasicMover playerMove;
    SquarePartitioner part;
    MazeRunner maze(&mazeGen, &part, &playerMove, true, true);

    MazeVisualizer visual(&maze);
    AnimatedMaze animator(&maze);
    animator.reset();

    ScreenHandler screen(&canvas, &input, &visual);

    input.addIdleReceiver(&animator, &AnimatedMaze::tick);

    glutMainLoop();

    input.removeActiveHandler();
    animator.stop();

    return 0;
}