#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../DrawingCanvas.h"
#include "Point.h"
#include "Positionable.h"

class Drawable : public virtual Positionable
{
public:
    virtual void draw(const DrawingCanvas* canvas) = 0;

};

#endif // DRAWABLE_H
