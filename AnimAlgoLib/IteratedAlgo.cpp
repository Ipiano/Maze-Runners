#include "IteratedAlgo.h"

IteratedAlgo::IteratedAlgo()
{

}

void IteratedAlgo::start()
{
    _isRunning = true;

    reset();
}

void IteratedAlgo::quit()
{
    _isRunning = false;
}

void IteratedAlgo::step()
{
    if(_isRunning)
        tick();
}

bool IteratedAlgo::running()
{
    return _isRunning;
}
