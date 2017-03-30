#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include "InputSignaler.h"
#include "DrawingCanvas.h"
#include "Widgets/Widget.h"

#include <vector>

class ScreenHandler
{
public:
    ScreenHandler(DrawingCanvas* canvas, InputSignaler* input, Widget* layout);
    virtual ~ScreenHandler(){}
};

#endif // SCREENHANDLER_H
