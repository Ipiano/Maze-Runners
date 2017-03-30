#ifndef _LAYOUT_H
#define _LAYOUT_H

#include "../Widget.h"
#include "../Positionable.h"
#include "../../DrawingCanvas.h"

#include <vector>
#include <unordered_map>

class Layout : public virtual Widget
{
    double _width, _height;
    Point _loc;

protected:
    std::vector<Widget*> _children;

    virtual void _layout(const Point& p, const double& w, const double& h) = 0;
public:
    void addWidget(Widget* w);
    void removeWidget(Widget* w);

    double minWidth(){return 0;}
    double minHeight(){return 0;}
    
    double height() final {return _height;}
    double width() final {return _width;}
    Point position() final {return _loc;}

    void setWidth(double width) final;
    void setHeight(double height) final;
    void setPosition(Point p) final;
    void setKeyPressInput(KeyPressSignaler* input) final;
    void setClickInput(MouseClickSignaler* input) final;

    virtual void draw(const DrawingCanvas* canvas) final;

};

#endif