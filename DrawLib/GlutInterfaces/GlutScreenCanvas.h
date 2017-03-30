#ifndef GLUTSCREENCANVAS_H
#define GLUTSCREENCANVAS_H

#include <string>
#include <GL/glut.h>

#include "../IOInterfaces/DrawingCanvas.h"
#include "../IOInterfaces/InputSignaler.h"

class GlutScreenCanvas : public DrawingCanvas
{
    unsigned int _window;
    unsigned int _width;
    unsigned int _height;

public:
    GlutScreenCanvas();
    void init(int& argc, char** argv, const std::string& windowName, const unsigned int& width, const unsigned int& height);
    void resize(const unsigned int& width, const unsigned int& height);
    void redraw();

    void drawBitmap(const unsigned int& width, const unsigned int& height, const unsigned int& x, const unsigned int& y, const unsigned char* bits) const;

};

#endif // GLUTSCREENCANVAS_H
