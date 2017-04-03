#ifndef MAZEVISUALIZER_H
#define MAZEVISUALIZER_H

#include "./Maze/mazerunnerbase.h"
#include "DrawingCanvas.h"
#include "Widget.h"
#include "Point.h"

#include <unordered_map>

class MazeVisualizer : public Widget
{
    struct color
    {
        unsigned char r, g, b;
    };
    unsigned int _width = 0, _height = 0;
    Point _loc;

    MazeRunnerBase* _maze = nullptr;
    unsigned char* _buffer = nullptr;
    unsigned int _bufferSize, _buffW, _buffH;
    unsigned int _mwidth, _mheight;
    unsigned int _cellW, _cellH;
    unsigned int _exW, _exH;
    unsigned int _wall;
    std::unordered_map<unsigned int, std::unordered_map<unsigned int, color>> _paths;

    void _drawCell(const unsigned int& x, const unsigned int& y, const MapTile& tile);
    void _drawCell(const unsigned int& x, const unsigned int& y, const MapTile& tile, const color& rgb);
    color _getColor(const unsigned int& x, const unsigned int& y);
    void _addColor(const unsigned int& x, const unsigned int& y, const color& rgb);

public:
    MazeVisualizer(MazeRunnerBase* m);
    ~MazeVisualizer();

    void draw(const DrawingCanvas* display);

    virtual double minWidth();
    virtual double minHeight();
    virtual double height();
    virtual double width();
    virtual Point position();

    virtual void setWidth(double width);
    virtual void setHeight(double height);
    virtual void setPosition(Point p);
};

#endif // MAZEVISUALIZER_H
