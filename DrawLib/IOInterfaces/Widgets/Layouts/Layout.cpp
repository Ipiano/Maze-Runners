#include "Layout.h"

#include <algorithm>

using namespace std;

void Layout::addWidget(Widget* w)
{
    if(find(_children.begin(), _children.end(), w) == _children.end())
    {
        _children.push_back(w);
        _layout(_loc, _width, _height);
    }
}

void Layout::removeWidget(Widget* w)
{
    auto iter = find(_children.begin(), _children.end(), w);
    if(iter != _children.end())
    {
        _children.erase(iter);
        _layout(_loc, _width, _height);
    }
}

void Layout::setWidth(double width)
{
    _width = width;
    _layout(_loc, _width, _height);
}

void Layout::setHeight(double height)
{
    _height = height;
    _layout(_loc, _width, _height);
}

void Layout::setPosition(Point p)
{
    _loc = p;
    _layout(_loc, _width, _height);
}

void Layout::setKeyPressInput(KeyPressSignaler* input)
{
    Widget::setKeyPressInput(input);
    for(Widget*& w : _children)
        w->setKeyPressInput(input);
}

void Layout::setClickInput(MouseClickSignaler* input)
{
    Widget::setClickInput(input);
    for(Widget*& w : _children)
        w->setClickInput(input);
}

void Layout::draw(const DrawingCanvas* canvas)
{
    for(Widget*& w : _children)
        w->draw(canvas);
}