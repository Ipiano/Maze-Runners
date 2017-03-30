#include "ScreenHandler.h"

#include <iostream>

using namespace std;

ScreenHandler::ScreenHandler(DrawingCanvas* canvas, InputSignaler* input, Widget* draw)
{
    input->addRedisplayReceiver(canvas, &DrawingCanvas::redraw);
    input->addResizeReceiver(canvas, &DrawingCanvas::resize);

    canvas->addDrawReceiver(draw, &Widget::draw);
    input->addResizeReceiver(
    [draw](const unsigned int& w, const unsigned int& h)
    {
        draw->setWidth(w);
        draw->setHeight(h);
    });

}