#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint;

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

    unsigned char exits; //Each of last 4 bytes corresponds to valid exit direction
};

struct MazeSettings
{
    const int& map_width;
    const int& map_height;       //May be -1, -1 for unknown size

    const bool& map_wraps;        //Whether or not the map wraps around on the edges

    const int& exit_x;
    const int& exit_y;           //Maze exit relative to player start; -1, -1 for unknown
};


#endif // TYPES_H
