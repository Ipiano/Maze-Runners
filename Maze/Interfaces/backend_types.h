#ifndef _BACKEND_TYPES_H
#define _BACKEND_TYPES_H

#include "../types.h"
#include "../attributeTypes.h"
#include <vector>
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>

struct BasicPlayerData
{
    unsigned int x, y;
    int id;
};

struct AdvancedPlayerData
{
    unsigned int x, y;
    int id;

    int ticksPerTurn;
    int mapVisionDist;
    int playerVisionDist;
    int ticksLeftForCurrentMove;
    int wallBreaksLeft;
    int wallPhaseLeft;
    int luckLeft;
    int willLeft;
    int stickyBombs;
    AdvancedPlayerMove moveInProgress;
};

struct point
{
    unsigned int x, y;

    bool operator ==(const point& other){return x == other.x && y == other.y;}
};

template<class Tile>
class maze
{
public:
    class iterator
    {
        friend class maze;
        friend std::ostream& operator<<(std::ostream& out, const typename maze<Tile>::iterator& m);
        Tile* _curr;
        
        iterator(Tile* ptr) : _curr(ptr){};
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

            Tile& operator*(){return *_curr;}
            Tile* operator->(){return _curr;}
    };

private:
    Tile* _maze = nullptr;
    unsigned int _w, _h;
    bool _wrapped;

public:
    std::vector<point> players;
    point exit;

    maze(){}
    maze(Tile* data, unsigned int width, unsigned int height, bool wrapped) : _maze(data), _w(width), _h(height), _wrapped(wrapped){}
    unsigned int width() const {return _w;}
    unsigned int height() const {return _h;}
    bool wrapped() const {return _wrapped;}

    Tile& at(const unsigned int& x, const unsigned int& y)
    {
        if(x < 0 || x >= _w ||  y < 0 ||  y >= _h)
            throw std::out_of_range("Attempted to access " + std::to_string(x) + ", " + std::to_string(y) + " in maze size " +
            std::to_string(_w) + ", " + std::to_string(_h));
        return *(_maze + _w*y + x);
    }

    Tile& at(const point& loc)
    {
        return at(loc.x, loc.y);
    }

    iterator begin() {return iterator(_maze);}
    iterator end()  {return iterator(_maze+_w*_h+1);}
    iterator cbegin() {return iterator(_maze+_w*_h);}
    iterator cend() {return iterator(_maze-1);}

    bool valid() const {return _maze != nullptr;}
    void destroy() {delete[] _maze; _maze=nullptr;}
};

template<class T>
inline std::ostream& operator<<(std::ostream& out, const typename maze<T>::iterator& m)
{
    return out << m._curr;
}

#endif