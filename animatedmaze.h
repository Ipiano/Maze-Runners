#ifndef ANIMATEDMAZE_H
#define ANIMATEDMAZE_H

#include "IteratedAlgo.h"
#include "DrawingCanvas.h"
#include "mazevisualizer.h"
#include "./Maze/mazerunnerbase.h"

class AnimatedMaze : public IteratedAlgo
{
    MazeRunnerBase* _maze;

public:
    AnimatedMaze(MazeRunnerBase* m);

    void stop();
    virtual void reset();
    virtual void tick();
};

#endif // ANIMATEDMAZE_H
