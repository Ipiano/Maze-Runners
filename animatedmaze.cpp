#include "animatedmaze.h"

#include <GL/freeglut.h>
#include <iostream>

using namespace std;

AnimatedMaze::AnimatedMaze(MazeRunner* m) : _loader(m), _maze(m)
{
}

void AnimatedMaze::stop()
{
    quit();
}

void AnimatedMaze::reset()
{
    _loader.unloadPlayers();
    _loader.loadPlayers("./Players");
    _maze->setup();
}

void AnimatedMaze::tick()
{
    if(!_maze->tickGame())
    {
        cout << "Maze done!" << endl;
        quit();
    }

    glutPostRedisplay();
}
