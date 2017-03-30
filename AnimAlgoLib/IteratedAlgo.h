#ifndef ITERATEDALGO_H
#define ITERATEDALGO_H

#include "AnimateableAlgo.h"

class IteratedAlgo : public AnimateableAlgo
{
    bool _isRunning = false;

public:
    void start() final;
    void step() final;
    void quit() final;

    bool running() final;

    IteratedAlgo();

    virtual void reset(){}
    virtual void tick(){}
};

#endif // ITERATEDALGO_H
