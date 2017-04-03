#ifndef TYPES_H
#define TYPES_H

#include <vector>

typedef unsigned int uint;

struct MazePoint
{
    int x, y;
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
    bool hasStickyBomb = false;
    unsigned char exits; //Each of last 4 bytes corresponds to valid exit direction
};

struct PlayerAttributes
{
    unsigned int speed;         //Determines how long moving from one tile to another takes
    unsigned int intelligence;  //Determines how far around the player they see
    unsigned int strength;      //Determines how many times the player can break a wall
    unsigned int luck;          //Determines how many times the player can use the 'luck' move
    unsigned int mysticality;   //Determines how many times the player can phase through a wall
    unsigned int cunning;       //Determines how many times the player can drop a sticky bomb
    unsigned int sense;         //Determines how far around the player can sense other players
};

enum class Move
{
    NOOP,
    MOVETO,
    WALLBREAK,
    WALLPHASE,
    STICKYBOMB,
    LUCK
};

struct PlayerMove
{
    Move attemptedMove;     //One of the enum Move types
    MazePoint destination;  //Used for MoveTo. Location must be one step away, or previously visited
    MapTile::Direction dir; //Used for wallbreak and wall phase

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
    int map_width;
    int map_height;       //May be -1, -1 for unknown size

    bool map_wraps;        //Whether or not the map wraps around on the edges

    int exit_x;
    int exit_y;           //Maze exit relative to player start; -1, -1 for unknown
};


#endif // TYPES_H
