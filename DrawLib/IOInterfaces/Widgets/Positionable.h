#ifndef _POSITIONABLE_H
#define _POSITIONABLE_H

#include "Point.h"

class Positionable
{
public:
    virtual double width() = 0;
    virtual double height() = 0;
    virtual Point position() = 0;

    virtual void setWidth(double width) = 0;
    virtual void setHeight(double height) = 0;
    virtual void setPosition(Point p) = 0;
};

#endif