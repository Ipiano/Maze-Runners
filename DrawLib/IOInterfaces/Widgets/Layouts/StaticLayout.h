#ifndef _STATIC_LAYOUT_H
#define _STATIC_LAYOUT_H

#include "Layout.h"

class StaticLayout : public Layout
{
    double _width, _height;

protected:
    virtual double minWidth(){return _width;}
    virtual double minHeight(){return _height;}
    virtual void _layout(const Point& p, const double& w, const double& h);
};

#endif