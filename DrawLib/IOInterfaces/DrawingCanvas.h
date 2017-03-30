#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include "InputSignaler.h"

class DrawingCanvas : public DrawSignaler
{
public:
    virtual void redraw() = 0;
    virtual void resize(const unsigned int& width, const unsigned int& height) = 0;

    virtual void drawBitmap(const unsigned int& width, const unsigned int& height, const unsigned int& x, const unsigned int& y, const unsigned char* bits) const = 0;
};

#endif // DRAWINGCANVAS_H