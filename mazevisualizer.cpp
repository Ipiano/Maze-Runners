#include "mazevisualizer.h"

#include <iostream>
#include <exception>

using namespace std;

MazeVisualizer::MazeVisualizer(MazeRunner* m) : _maze(m)
{

}

MazeVisualizer::~MazeVisualizer()
{
    delete[] _buffer;
}

void MazeVisualizer::_addColor(const unsigned int& x, const unsigned int& y, const color& rgb)
{
    color& old = _paths[x][y];
    old.r = std::min(old.r+rgb.r, 128);
    old.g = std::min(old.g+rgb.g, 128);
    old.b = std::min(old.b+rgb.b, 128);
}

MazeVisualizer::color MazeVisualizer::_getColor(const unsigned int& x, const unsigned int& y)
{
    point ex = _maze->getMaze().exit;
    if(x == ex.x && y == ex.y) return color{102, 255, 102};

    auto xit = _paths.find(x);
    if(xit != _paths.end())
    {
        auto yit = (*xit).second.find(y);
        if(yit != (*xit).second.end())
            return (*yit).second;
    }

    return color{0, 0, 0};
}

void MazeVisualizer::_drawCell(const unsigned int& x, const unsigned int& y, const MapTile& tile)
{
    color rgb = _getColor(x, y);
    _drawCell(x, y, tile, rgb);
}

void MazeVisualizer::_drawCell(const unsigned int& x, const unsigned int& y, const MapTile& tile, const color& rgb)
{
    if(x < 0 || x >= _mwidth || y < 0 || y >= _mheight) return;
    unsigned int y_ = _mheight-y-1;

    //cerr << "Draw cell " << x << ", " << y_ << " : " << (int)rgb.r << ", " << (int)rgb.g << ", " << (int)rgb.b << endl;

    unsigned int thsH = _cellH + (y_<_exH?1:0);
    unsigned int thsW = _cellW + (x<_exW?1:0);

    //cerr << _cellW << " -> " << thsW << ", " << _cellH << " -> " << thsH << endl;

    int rowBytes = _buffW*_cellH*3;
    int skipBytes = _cellW*3*x + (x<_exW?x*3:_exW*3);

    //cerr << "Skip " << _cellW*3*x << " -> " << skipBytes << endl;

    unsigned char* start = _buffer + rowBytes*(y_+1) + (y_<_exH?(y_+1)*_buffW*3:_exH*_buffW*3) - _buffW*3 + skipBytes;

    //cerr << "Row offset " << (y_<_exH?(y_+1)*_buffW:_exH*_buffW) << endl;
    //cerr << "Total offset " << rowBytes*(y_+1) + (y_<_exH?(y_+1)*_buffW*3:_exH*_buffW*3) - _buffW*3 + skipBytes << endl;

    bool north = ((tile.exits & (unsigned char)MapTile::Direction::NORTH) == 0);
    bool south = ((tile.exits & (unsigned char)MapTile::Direction::SOUTH) == 0);
    bool east = ((tile.exits & (unsigned char)MapTile::Direction::EAST) == 0);
    bool west = ((tile.exits & (unsigned char)MapTile::Direction::WEST) == 0);

    //cerr << north << " : " << south << " : " << east << " : " << west << endl;

    for(int i=0; i<thsH; i++)
    {
        unsigned char* iter = start - _buffW*i*3;
        //cerr << "\t" << _buffW*i*3 << endl;
        for(int j=0; j<thsW; j++)
        {
            if((north && i < _wall) || (south && i >= _cellH-_wall)
                || (west && j < _wall) || (east && j >= _cellW-_wall))
            {
                //cerr << "\t\tWall" << endl;
                *(iter++) = *(iter++) = *(iter++) = 255;
            }
            else
            {
                //cerr << "\t\tFloor" << endl;
                *(iter++) = rgb.r;
                *(iter++) = rgb.g;
                *(iter++) = rgb.b;
            }
        }
    }
    
}

void MazeVisualizer::draw(const DrawingCanvas* display)
{
    if(_maze == nullptr)
    {
        cout << "No maze to draw!" << endl;
        return;
    }
       
    auto& maze = _maze->getMaze();
    _mwidth = maze.width();
    _mheight = maze.height();

    if(!maze.valid())
    {
        cout << "Cannot draw empty maze!" << endl;
        return;
    }

    if(_buffer == nullptr)
    {
        //cerr << "Maze is " << _mwidth << " x " << _mheight << endl;

        _cellW = _width/(double)_mwidth;
        _cellH = _height/(double)_mheight;
        _exW = _width - _mwidth*_cellW;
        _exH = _height - _mheight*_cellH;

        //cerr << "Remaining space " << _exW << ", " << _exH << endl;

        _wall = (int)std::min(_cellW, _cellH)*0.1;
        if(_cellW > 1 && _cellH > 1 && _wall < 1) _wall = 1;

        //cout << "Drawing maze with " << _cellW << " px x " << _cellH << " px cells and " << _wall << " px walls" << endl;

        _buffW = _width;
        _buffH = _height;
        _bufferSize = _buffW*_buffH*3;

        //cout << "Buffer is " << _buffW << " x " << _buffH << " = " << _bufferSize << endl;

        if(_cellW == 0 || _cellH == 0)
        {
            cout << "Maze too big for " << _width << " x " << _height << endl;
            return;
        }
        _buffer = new unsigned char[_bufferSize];

        auto iter = maze.begin();
        for(unsigned int i=0; i<_mheight; i++)
        {
            for(unsigned int j=0; j<_mwidth; j++)
            {
                _drawCell(j, i, *(iter++));
            }
        }
        
        //cerr << "Maze drawn" << endl;
    }

    std::unordered_map<Player*, unsigned int>* players = _maze->getPlayerData();

    //Redraw places players were previously
    for(auto p : *players)
    {
        //cout << "Draw player " << p.first << " : " << p.second << endl;
        unsigned char* pcolor = p.first->playerColor();
        point ploc = maze.players[p.second];

        _addColor(ploc.x, ploc.y, color{pcolor[0]/3, pcolor[1]/3, pcolor[2]/3});

        try{
            _drawCell(ploc.x+1, ploc.y, maze.at(point{ploc.x+1, ploc.y}));
        }catch(exception& ex){}
        try{
            _drawCell(ploc.x-1, ploc.y, maze.at(point{ploc.x-1, ploc.y}));
        }catch(exception& ex){}
        try{  
            _drawCell(ploc.x, ploc.y+1, maze.at(point{ploc.x, ploc.y+1}));
        }catch(exception& ex){}
        try{        
            _drawCell(ploc.x, ploc.y-1, maze.at(point{ploc.x, ploc.y-1}));
        }catch(exception& ex){}
    }

    //Draw players
    for(auto p : *players)
    {
        //cout << "Draw player " << p.first << " : " << p.second << endl;
        unsigned char* pcolor = p.first->playerColor();
        point ploc = maze.players[p.second];

        _drawCell(ploc.x, ploc.y, maze.at(point{ploc.x, ploc.y}), color{pcolor[0], pcolor[1], pcolor[2]});
    }

    //Draw exit
    _drawCell(maze.exit.x, maze.exit.y, maze.at(maze.exit));

    if(_buffer != nullptr)
        display->drawBitmap(_buffW, _buffH, _loc.x, _loc.y, _buffer);
}

double MazeVisualizer::minWidth()
{
    return _mwidth*3;
}

double MazeVisualizer::minHeight()
{
    return _mheight*3;
}

double MazeVisualizer::height()
{
    return _height;
}

double MazeVisualizer::width()
{
    return _width;
}

Point MazeVisualizer::position()
{
    return _loc;
}

void MazeVisualizer::setWidth(double width)
{
    delete[] _buffer;
    _buffer = nullptr;

    _width = width;
}

void MazeVisualizer::setHeight(double height)
{
    delete[] _buffer;
    _buffer = nullptr;

    _height = height;
}

void MazeVisualizer::setPosition(Point p)
{
    _loc = p;
}
