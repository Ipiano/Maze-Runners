#ifndef ANIMATEDMAZE_H
#define ANIMATEDMAZE_H

#include "IteratedAlgo.h"
#include "DrawingCanvas.h"
#include "mazevisualizer.h"
#include "./Maze/mazerunner.h"
#include "./Maze/playerloader.h"

class AnimatedMaze : public IteratedAlgo
{
    PlayerLoader _loader;
    MazeRunner* _maze;

public:
    AnimatedMaze(MazeRunner* m);

    void stop();
    virtual void reset();
    virtual void tick();
};

#endif // ANIMATEDMAZE_H
