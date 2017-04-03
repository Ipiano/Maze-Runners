#include "animatedmaze.h"

#include <GL/freeglut.h>
#include <iostream>

using namespace std;

AnimatedMaze::AnimatedMaze(MazeRunnerBase* m) : _maze(m)
{
}

void AnimatedMaze::stop()
{
    quit();
}

void AnimatedMaze::reset()
{
    _maze->setup();
}

void AnimatedMaze::tick()
{
    if(!_maze->tickGame())
    {
        quit();
    }
}
