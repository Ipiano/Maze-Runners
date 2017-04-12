#ifndef MAZEVISUALIZER_H
#define MAZEVISUALIZER_H

#include "./Maze/mazerunnerbase.h"
#include "DrawingCanvas.h"
#include "Widget.h"
#include "Point.h"

#include <iostream>
#include <exception>
#include <unordered_map>

template<class PlayerType, class PlayerDataType, class Tile>
class MazeVisualizer : public Widget
{
    struct color
    {
        unsigned char r, g, b;
    };
    unsigned int _width = 0, _height = 0;
    Point _loc;

    MazeRunnerAccess<PlayerType, PlayerDataType, Tile>* _maze = nullptr;
    unsigned char* _buffer = nullptr;
    unsigned int _bufferSize, _buffW, _buffH;
    unsigned int _mwidth, _mheight;
    unsigned int _cellW, _cellH;
    unsigned int _exW, _exH;
    unsigned int _wall;
    std::unordered_map<unsigned int, std::unordered_map<unsigned int, color>> _paths;
    std::unordered_map<PlayerType*, point> _playerLocations;
    std::unordered_map<PlayerType*, Tile> _playerTiles;

    void _drawCell(const unsigned int& x, const unsigned int& y, const Tile& tile);
    void _drawCell(const unsigned int& x, const unsigned int& y, const Tile& tile, const color& rgb);
    color _getColor(const unsigned int& x, const unsigned int& y);
    void _addColor(const unsigned int& x, const unsigned int& y, const color& rgb);

public:
    MazeVisualizer(MazeRunnerAccess<PlayerType, PlayerDataType, Tile>* m);
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

using std::min;
using std::cout;
using std::endl;
using std::exception;

template<class PlayerType, class PlayerDataType, class Tile>
MazeVisualizer<PlayerType, PlayerDataType, Tile>::MazeVisualizer(MazeRunnerAccess<PlayerType, PlayerDataType, Tile>* m) : _maze(m)
{

}

template<class PlayerType, class PlayerDataType, class Tile>
MazeVisualizer<PlayerType, PlayerDataType, Tile>::~MazeVisualizer()
{
    delete[] _buffer;
}

template<class PlayerType, class PlayerDataType, class Tile>
void MazeVisualizer<PlayerType, PlayerDataType, Tile>::_addColor(const unsigned int& x, const unsigned int& y, const color& rgb)
{
    color& old = _paths[x][y];
    old.r = std::min(old.r+rgb.r, 128);
    old.g = std::min(old.g+rgb.g, 128);
    old.b = std::min(old.b+rgb.b, 128);
}

template<class PlayerType, class PlayerDataType, class Tile>
typename MazeVisualizer<PlayerType, PlayerDataType, Tile>::color MazeVisualizer<PlayerType, PlayerDataType, Tile>
::_getColor(const unsigned int& x, const unsigned int& y)
{
    static unsigned char c[3];
    if(_maze->getMaze().at(x, y).getColor(c))
        return color{c[0], c[1], c[2]};

    auto xit = _paths.find(x);
    if(xit != _paths.end())
    {
        auto yit = (*xit).second.find(y);
        if(yit != (*xit).second.end())
            return (*yit).second;
    }

    return color{0, 0, 0};
}

template<class PlayerType, class PlayerDataType, class Tile>
void MazeVisualizer<PlayerType, PlayerDataType, Tile>::_drawCell(const unsigned int& x, const unsigned int& y, const Tile& tile)
{
    color rgb = _getColor(x, y);
    _drawCell(x, y, tile, rgb);
}

template<class PlayerType, class PlayerDataType, class Tile>
void MazeVisualizer<PlayerType, PlayerDataType, Tile>::_drawCell(const unsigned int& x, const unsigned int& y, const Tile& tile, const color& rgb)
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
    //bool south = ((tile.exits & (unsigned char)MapTile::Direction::SOUTH) == 0);
    //bool east = ((tile.exits & (unsigned char)MapTile::Direction::EAST) == 0);
    bool west = ((tile.exits & (unsigned char)MapTile::Direction::WEST) == 0);

    //cerr << north << " : " << south << " : " << east << " : " << west << endl;

    for(uint i=0; i<thsH; i++)
    {
        unsigned char* iter = start - _buffW*i*3;
        //cerr << "\t" << _buffW*i*3 << endl;
        for(uint j=0; j<thsW; j++)
        {
            if((north && i < _wall) ||
               (west && j < _wall))
            {
                //cerr << "\t\tWall" << endl;
                *(iter++) = *(iter++) = *(iter++) = 0;
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

template<class PlayerType, class PlayerDataType, class Tile>
void MazeVisualizer<PlayerType, PlayerDataType, Tile>::draw(const DrawingCanvas* display)
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

    //Check if any player didn't move, and the tile they were on changed
    //Then we need to redraw the whole maze
    std::unordered_map<PlayerType*, PlayerDataType>* players = _maze->getPlayerData();
    for(const auto& p : *players)
    {
        auto& pLoc = _playerLocations[p.first];
        auto& pTile = _playerTiles[p.first];
        auto mTile = maze.at(p.second.x, p.second.y);
        if(pLoc.x != p.second.x || pLoc.y != p.second.y)
        {
            if(_buffer)
            {
                _drawCell(pLoc.x, pLoc.y, pTile);
            }
            pLoc = point{p.second.x, p.second.y};

            //Only add player colors when they move
            unsigned char* pcolor = p.first->playerColor();

            unsigned char r = pcolor[0]/3;
            unsigned char g = pcolor[1]/3;
            unsigned char b = pcolor[2]/3;

            _addColor(pLoc.x, pLoc.y, color{r, g, b});
        }
        else if(pTile != mTile)
        {
            if(_buffer)
            {
                delete[] _buffer;
                _buffer = nullptr;
            }
        }
        pTile = mTile;
    }

    if(_buffer == nullptr)
    {
        //cerr << "Maze is " << _mwidth << " x " << _mheight << endl;

        _cellW = _width/(double)_mwidth;
        _cellH = _height/(double)_mheight;
        _exW = _width - _mwidth*_cellW;
        _exH = _height - _mheight*_cellH;

        //cerr << "Remaining space " << _exW << ", " << _exH << endl;

	
        _wall = (int)std::min(_cellW, _cellH)*0.3;
        if(_cellW > 1 && _cellH > 1 && _wall < 1) _wall = 1;
	
	
        //cout << "Drawing maze with " << _cellW << " px x " << _cellH << " px cells and " << _wall << " px walls" << endl;

        _buffW = _width;
        _buffH = _height;
        _bufferSize = _buffW*_buffH*3;

        //cout << "Buffer is " << _buffW << " x " << _buffH << " = " << _bufferSize << endl;

        if(_cellW > 0 || _cellH > 0)
        {
            _buffer = new unsigned char[_bufferSize];

            auto iter = maze.begin();
            for(unsigned int i=0; i<_mheight; i++)
            {
                for(unsigned int j=0; j<_mwidth; j++)
                {
                    _drawCell(j, i, *(iter++));
                }
            }
        }
        
        //cerr << "Maze drawn" << endl;
    }

    if(_buffer == nullptr) return;

    //Draw players
    for(auto p : *players)
    {
        //cout << "Draw player " << p.first << " : " << p.second << endl;
        unsigned char* pcolor = p.first->playerColor();
        point ploc = point{p.second.x, p.second.y};

        _drawCell(ploc.x, ploc.y, maze.at(point{ploc.x, ploc.y}), color{pcolor[0], pcolor[1], pcolor[2]});
    }

    //Draw exit
    _drawCell(maze.exit.x, maze.exit.y, maze.at(maze.exit));


    if(_buffer != nullptr)
    {
        display->drawBitmap(_buffW, _buffH, _loc.x, _loc.y, _buffer);
    }
}

template<class PlayerType, class PlayerDataType, class Tile>
double MazeVisualizer<PlayerType, PlayerDataType, Tile>::minWidth()
{
    return _mwidth*3;
}

template<class PlayerType, class PlayerDataType, class Tile>
double MazeVisualizer<PlayerType, PlayerDataType, Tile>::minHeight()
{
    return _mheight*3;
}

template<class PlayerType, class PlayerDataType, class Tile>
double MazeVisualizer<PlayerType, PlayerDataType, Tile>::height()
{
    return _height;
}

template<class PlayerType, class PlayerDataType, class Tile>
double MazeVisualizer<PlayerType, PlayerDataType, Tile>::width()
{
    return _width;
}

template<class PlayerType, class PlayerDataType, class Tile>
Point MazeVisualizer<PlayerType, PlayerDataType, Tile>::position()
{
    return _loc;
}

template<class PlayerType, class PlayerDataType, class Tile>
void MazeVisualizer<PlayerType, PlayerDataType, Tile>::setWidth(double width)
{
    delete[] _buffer;
    _buffer = nullptr;

    _width = width;
}

template<class PlayerType, class PlayerDataType, class Tile>
void MazeVisualizer<PlayerType, PlayerDataType, Tile>::setHeight(double height)
{
    delete[] _buffer;
    _buffer = nullptr;

    _height = height;
}

template<class PlayerType, class PlayerDataType, class Tile>
void MazeVisualizer<PlayerType, PlayerDataType, Tile>::setPosition(Point p)
{
    _loc = p;
}


#endif // MAZEVISUALIZER_H
