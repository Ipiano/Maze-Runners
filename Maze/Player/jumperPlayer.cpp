#include "jumperPlayer.h"

#include <iostream>

using namespace std;

MazePoint operator + (const MazePoint& l, const MazePoint& r)
{
    return MazePoint{l.x + r.x, l.y + r.y};
}

MazePoint operator - (const MazePoint& l, const MazePoint& r)
{
    return MazePoint{l.x - r.x, l.y - r.y};
}

//Get all directions that can be moved to from a point
//which aren't known dead ends or already visited
void JumperPlayer::getValidDirections(const MazePoint& loc, vector<MazePoint>& out)
{
    MapTile& t = explored[loc.x][loc.y];
    out.clear();
    //cerr << "Getting valid dirs from " << loc.x << ", " << loc.y << endl;
    //cerr << (int)(t.exits & (unsigned char)MapTile::Direction::NORTH) << " | " << !dead[loc.x][loc.y-1] << " | " << endl;
    //cerr << (int)(t.exits & (unsigned char)MapTile::Direction::SOUTH) << " | " << !dead[loc.x][loc.y+1] << " | " << endl;
    //cerr << (int)(t.exits & (unsigned char)MapTile::Direction::EAST) << " | " << !dead[loc.x+1][loc.y] << " | " << endl;
    //cerr << (int)(t.exits & (unsigned char)MapTile::Direction::WEST) << " | " << !dead[loc.x-1][loc.y] << " | " << endl;

    if(t.exits & (unsigned char)MapTile::Direction::NORTH && !dead[loc.x][loc.y-1] )
        out.push_back(MazePoint{0, -1});
    if(t.exits & (unsigned char)MapTile::Direction::SOUTH && !dead[loc.x][loc.y+1] )
        out.push_back(MazePoint{0, 1});
    if(t.exits & (unsigned char)MapTile::Direction::EAST && !dead[loc.x+1][loc.y] )
        out.push_back(MazePoint{1, 0});
    if(t.exits & (unsigned char)MapTile::Direction::WEST && !dead[loc.x-1][loc.y] )
        out.push_back(MazePoint{-1, 0});
}

//Get all directions that can be moved to from a point
//which aren't known dead ends or already visited
void JumperPlayer::getValidMoves(const MazePoint& loc, vector<MazePoint>& out)
{
    MapTile& t = explored[loc.x][loc.y];
    out.clear();
    //cerr << "Getting valid moves from " << loc.x << ", " << loc.y << endl;
    //cerr << (int)(t.exits & (unsigned char)MapTile::Direction::NORTH) << " | " << !dead[loc.x][loc.y-1] << " | " << !visited[loc.x][loc.y-1] << endl;
    //cerr << (int)(t.exits & (unsigned char)MapTile::Direction::SOUTH) << " | " << !dead[loc.x][loc.y+1] << " | " << !visited[loc.x][loc.y+1] << endl;
    //cerr << (int)(t.exits & (unsigned char)MapTile::Direction::EAST) << " | " << !dead[loc.x+1][loc.y] << " | " << !visited[loc.x+1][loc.y] << endl;
    //cerr << (int)(t.exits & (unsigned char)MapTile::Direction::WEST) << " | " << !dead[loc.x-1][loc.y] << " | " << !visited[loc.x-1][loc.y] << endl;

    if(t.exits & (unsigned char)MapTile::Direction::NORTH && !dead[loc.x][loc.y-1] && !visited[loc.x][loc.y-1])
        out.push_back(MazePoint{0, -1});
    if(t.exits & (unsigned char)MapTile::Direction::SOUTH && !dead[loc.x][loc.y+1] && !visited[loc.x][loc.y+1])
        out.push_back(MazePoint{0, 1});
    if(t.exits & (unsigned char)MapTile::Direction::EAST && !dead[loc.x+1][loc.y] && !visited[loc.x+1][loc.y])
        out.push_back(MazePoint{1, 0});
    if(t.exits & (unsigned char)MapTile::Direction::WEST && !dead[loc.x-1][loc.y] && !visited[loc.x-1][loc.y])
        out.push_back(MazePoint{-1, 0});
}

bool JumperPlayer::nextToUnknown(const MazePoint& p)
{
    if(explored[p.x].find(p.y+1) == explored[p.x].end()) return true;
    if(explored[p.x].find(p.y-1) == explored[p.x].end()) return true;
    if(explored[p.x+1].find(p.y) == explored[p.x+1].end()) return true;
    if(explored[p.x-1].find(p.y) == explored[p.x-1].end()) return true;
    return false;
}

void JumperPlayer::bfsDead(const MazePoint& start)
{
    //Don't mark already known dead or visited places'
    if(visited[start.x][start.y] || (dead[start.x][start.y] && !nextToUnknown(start))) return;

    //cerr << "BFS from " << start.x << ", " << start.y << endl;
    static vector<MazePoint> dirs;
    getValidDirections(start, dirs);

    if(dirs.size() == 1)
    {
        //cerr << "Dead end!" << endl;
        dead[start.x][start.y] = true;
        bfsDead(dirs[0]);
    }
}

PlayerMove JumperPlayer::move(const MapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y)
{
    PlayerMove out;

    const MapTile& current = surroundings[loc_y*area_width + loc_x];
    if(current.uid != prevUid)
    {
        currLocation = nextLocation;
        if(teleported)
            backtrace.pop();
    }
    prevUid = current.uid;
    visited[currLocation.x][currLocation.y] = true;

    //Copy curroundings into local map
    auto iter = surroundings;
    for(uint j=0, j_ = currLocation.y - loc_y; j < area_height; j++, j_++)
        for(uint i=0, i_ = currLocation.x - loc_x; i < area_width; i++, i_++)
        {
            explored[i_][j_] = *(iter++);
        }

    //Fill in new dead ends
    for(int j=0, j_ = currLocation.y - loc_y; j < (int)area_height; j++, j_++)
        for(int i=0, i_ = currLocation.x - loc_x; i < (int)area_width; i++, i_++)
        {
            bfsDead(MazePoint{i_, j_});
        }

    static vector<MazePoint> moves;
    getValidMoves(currLocation, moves);

    //No moves means dead end; move back to last intersection
    if(moves.size() == 0)
    {
        if(backtrace.size())
        {
            MazePoint to = backtrace.top();

            teleported = true;
            out.attemptedMove = Move::MOVETO;
            out.destination = to - currLocation;

            nextLocation = currLocation + out.destination;
        }
        return out;
    }

    //Intersection, add it to our stack to jump back later
    //Only need to check > 1 because none of the moves included
    //contain the previous location
    if(moves.size() > 1)
        backtrace.push(currLocation);
    
    out.attemptedMove = Move::MOVETO;
    out.destination = moves[0];

    teleported = false;
    nextLocation = currLocation + out.destination;
    return out;
}
