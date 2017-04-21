#ifndef TYPES_H
#define TYPES_H

#include <vector>

typedef unsigned int uint;

struct MazePoint
{
    long long int x, y;
    MazePoint(long long int X=0, long long int Y=0) : x(X), y(Y) {}
};

struct MapTile
{
    enum class Direction : unsigned char
    {
        NONE = 0,
        NORTH = 1,
        EAST = 2,
        SOUTH = 4,
        WEST = 8
    };

    std::vector<unsigned int> players;
    unsigned int uid;
    bool isExit = false;
    unsigned char exits; //Each of last 4 bytes corresponds to valid exit direction

    bool operator !=(const MapTile& o)
    {
        return o.exits != exits;
    }

    bool getColor(unsigned char*& c)
    {
        if(isExit)
        {
            c[0] = c[2] = 100;
            c[1] = 255;
            return true;
        }
        return false;
    }
};
struct PlayerMove
{
    enum class Move
    {
        NOOP,
        MOVETO
    };

    Move attemptedMove;     //One of the enum Move types
    MazePoint destination;  //Used for MoveTo. Location must be one step away, or previously visited

    //Convenience constructor for converting maptile directions
    //to moves
    PlayerMove(MapTile::Direction _dir = MapTile::Direction::NONE)
    {
        switch(_dir)
        {
            default:
            case MapTile::Direction::NONE: attemptedMove = Move::NOOP; break;
            case MapTile::Direction::NORTH: 
                attemptedMove = Move::MOVETO; 
                destination = MazePoint{0, -1};
                break;
            case MapTile::Direction::SOUTH: 
                attemptedMove = Move::MOVETO; 
                destination = MazePoint{0, 1};
                break;
            case MapTile::Direction::EAST: 
                attemptedMove = Move::MOVETO; 
                destination = MazePoint{1, 0};
                break;
            case MapTile::Direction::WEST: 
                attemptedMove = Move::MOVETO; 
                destination = MazePoint{-1, 0};
                break;
        }
    }
};

struct MazeSettings
{
    uint map_width;
    uint map_height;

    bool map_wraps;        //Whether or not the map wraps around on the edges

    int exit_x;
    int exit_y;           //Maze exit relative to player start
    MazeSettings(uint w=0, uint h=0, bool mw=false, int ex=0, int ey=0) :
       map_width(w), map_height(h), map_wraps(mw), exit_x(ex), exit_y(ey) {}
};


#endif // TYPES_H
