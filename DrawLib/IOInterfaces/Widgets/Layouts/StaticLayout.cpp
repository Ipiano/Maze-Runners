#include "StaticLayout.h"

#include <cmath>
#include <iostream>

using namespace std;

void StaticLayout::_layout(const Point& p, const double& w, const double& h)
{
    if(_children.size())
    {
        double bottom, top, left, right;
        top = _children[0]->position().y;
        bottom = _children[0]->position().y+_children[0]->height();
        left = _children[0]->position().x;
        right = _children[0]->position().x+_children[0]->width();

        for(Widget*& w : _children)
        {
            Point l = w->position();
            top = std::min(top, l.y);
            bottom = std::max(bottom, l.y+w->height());
            left = std::min(left, l.x);
            right = std::max(right, l.x+w->width());
        }

        _width = right-left;
        _height = bottom-top;

    }

}
