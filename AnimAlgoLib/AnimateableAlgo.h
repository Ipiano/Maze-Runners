#ifndef ANIMATEABLEALGO_H
#define ANIMATEABLEALGO_H

class AnimateableAlgo
{
public:
    //Sets up the algorithm
    virtual void start() = 0;

    //Ticks the algorithm
    virtual void step() = 0;

    //Cancels the algorithm
    virtual void quit() = 0;

    //Returns whether or not the algorithm is running
    virtual bool running() = 0;
};

#endif // ANIMATEABLEALGO_H
