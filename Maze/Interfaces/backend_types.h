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
    unsigned long long int x, y;
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
    int stickyBombAvoids;
    int stickyBombs;
    AdvancedPlayerMove moveInProgress;
    AdvancedPlayerData(uint X=0, uint Y=0, int ID=0) : x(X), y(Y), id(ID) {}
};

struct point
{
    unsigned long long int x, y;

    bool operator ==(const point& other){return x == other.x && y == other.y;}
};

template<class Tile>
class maze
{
public:
    class iterator
    {
        friend class maze;
        friend std::ostream& operator<<(std::ostream& out, const typename maze<Tile>::iterator& m)
        {
            return out << m._curr;
        }
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
    Tile _out_of_bounds;
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
        {
            //Reset out of bounds tile and return it
            _out_of_bounds = Tile();
            return _out_of_bounds;
        }
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

#endif
