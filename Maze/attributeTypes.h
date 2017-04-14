#ifndef ATTRIB_TYPES_H
#define ATTRIB_TYPES_H

#include <vector>
#include <iostream>

typedef unsigned int uint;

struct AdvancedMapTile
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
    unsigned char exits=0; //Each of last 4 bytes corresponds to valid exit direction

    bool operator ==(const AdvancedMapTile& o)
    {
        return (o.uid == uid) && (o.hasStickyBomb == hasStickyBomb) && (o.exits == exits);
    }

    bool operator !=(const AdvancedMapTile& o)
    {
        return !(*this == o);
    }

    bool getColor(unsigned char* c)
    {
        if(isExit)
        {
            c[0] = c[2] = 100;
            c[1] = 255;
            return true;
        }

        if(hasStickyBomb)
        {
            c[0] = 100;
            c[1] = c[2] = 0;
            return true;
        }
        return false;
    }
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
    unsigned int agility;       //Determines how many times the player can avoid a sticky bomb
};

struct AdvancedPlayerMove
{
    enum class Move
    {
        NOOP,
        MOVETO,
        WALLBREAK,
        WALLPHASE,
        STICKYBOMB,
        LUCK
    };

    Move attemptedMove;     //One of the enum Move types
    MazePoint destination;  //Used for MoveTo. Location must be one step away, or previously visited
    AdvancedMapTile::Direction dir; //Used for wallbreak and wall phase

    //Convenience constructor for converting AdvancedMapTile directions
    //to moves
    AdvancedPlayerMove(AdvancedMapTile::Direction _dir = AdvancedMapTile::Direction::NONE) : dir(_dir)
    {
        switch(_dir)
        {
            default:
            case AdvancedMapTile::Direction::NONE: attemptedMove = Move::NOOP; break;
            case AdvancedMapTile::Direction::NORTH: 
                attemptedMove = Move::MOVETO; 
                destination = MazePoint{0, -1};
                break;
            case AdvancedMapTile::Direction::SOUTH: 
                attemptedMove = Move::MOVETO; 
                destination = MazePoint{0, 1};
                break;
            case AdvancedMapTile::Direction::EAST: 
                attemptedMove = Move::MOVETO; 
                destination = MazePoint{1, 0};
                break;
            case AdvancedMapTile::Direction::WEST: 
                attemptedMove = Move::MOVETO; 
                destination = MazePoint{-1, 0};
                break;
        }
    }
};

#endif // TYPES_H
