#ifndef _BACKEND_TYPES_H
#define _BACKEND_TYPES_H

#include "../types.h"
#include <vector>
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>

struct point
{
    unsigned x, y;

    bool operator ==(const point& other){return x == other.x && y == other.y;}
};

class maze
{
public:
    class iterator
    {
        friend class maze;
        friend std::ostream& operator<<(std::ostream& out, const maze::iterator& m);
        MapTile* _curr;
        
        iterator(MapTile* ptr) : _curr(ptr){};
        public:
            bool operator == (const iterator& other) {return _curr == other._curr;}
            bool operator != (const iterator& other) {return _curr != other._curr;}

            iterator& operator++(){_curr++; return *this;}
            iterator& operator--(){_curr--; return *this;}

            iterator operator++(int){_curr++; return iterator(_curr-1);}
            iterator operator--(int){_curr--; return iterator(_curr+1);}

            iterator operator +(unsigned int n){_curr += n; return *this;}
            iterator operator -(unsigned int n){_curr -= n; return *this;}

            iterator& operator +=(unsigned int n){_curr += n; return *this;}
            iterator& operator -=(unsigned int n){_curr -= n; return *this;}

            MapTile& operator*(){return *_curr;}
            MapTile* operator->(){return _curr;}
    };

private:
    MapTile* _maze = nullptr;
    unsigned int _w, _h;

public:
    std::vector<point> players;
    point exit;

    maze(){}
    maze(MapTile* data, unsigned int width, unsigned int height) : _maze(data), _w(width), _h(height){}
    unsigned int width() const {return _w;}
    unsigned int height() const {return _h;}

    MapTile& at(const point& loc)
    {
        if(loc.x < 0 || loc.x >= _w || loc.y < 0 || loc.y >= _h)
            throw std::out_of_range("Attempted to access " + std::to_string(loc.x) + ", " + std::to_string(loc.y) + " in maze size " +
            std::to_string(_w) + ", " + std::to_string(_h));
        return *(_maze + _w*loc.y + loc.x);
    }

    iterator begin() {return iterator(_maze);}
    iterator end()  {return iterator(_maze+_w*_h+1);}
    iterator cbegin() {return iterator(_maze+_w*_h);}
    iterator cend() {return iterator(_maze-1);}

    bool valid() const {return _maze != nullptr;}
    void destroy() {delete[] _maze; _maze=nullptr;}
};

inline std::ostream& operator<<(std::ostream& out, const maze::iterator& m)
{
    return out << m._curr;
}

#endif