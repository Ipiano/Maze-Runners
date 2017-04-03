#include "jumperPlayer.h"

using namespace std;

//Get all directions that can be moved to from a point
//which aren't known dead ends or already visited
void JumperPlayer::getValidDirections(const MazePoint& loc, vector<MazePoint>& out)
{
    MapTile& t = explored[loc.x][loc.y];
    out.clear();
    if(t.exits & (unsigned char)MapTile::Direction::NORTH && !dead[loc.x][loc.y-1] && !visited[loc.x][loc.y-1])
        out.push_back(MazePoint{0, -1});
    if(t.exits & (unsigned char)MapTile::Direction::SOUTH && !dead[loc.x][loc.y+1] && !visited[loc.x][loc.y+1])
        out.push_back(MazePoint{0, 1});
    if(t.exits & (unsigned char)MapTile::Direction::EAST && !dead[loc.x+1][loc.y] && !visited[loc.x+1][loc.y])
        out.push_back(MazePoint{1, 0});
    if(t.exits & (unsigned char)MapTile::Direction::WEST && !dead[loc.x-1][loc.y] && !visited[loc.x-1][loc.y])
        out.push_back(MazePoint{-1, 0});
}

void JumperPlayer::bfsDead(const MazePoint& start)
{
}

PlayerMove JumperPlayer::move(const MapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y)
{
    PlayerMove out

    const MapTile& current = surroundings[loc_y*area_width + loc_x];
    if(current.uid != prevUid)
    {
        visited[nextLocation.x][nextLocation.y] = true;
        currLocation = nextLocation;
    }

    auto iter = surroundings;
    for(int j=0; j_ = currLocation.y - loc_y; j < area_height; j++, j_++)
        for(int i=0, i_ = currLocation.x - loc_x; i < area_width; i++, i_++)
        {
            explored[i_][j_] = *(iter++);
        }

    static vector<MazePoint> moves;
    getValidDirections(current, moves);

    //No moves means dead end; move back to last intersection
    if(moves.size() == 0)
    {
        MazePoint to = backtrace.top();
        backtrace.pop();
        out.attemptedMove = Move::MOVETO;
        out.destination = MazePoint{to.x-currLocation.x, to.y-currLocation.y};
        return out;
    }
    //Intersection, add it to our stack to jump back later
    //Only need to check > 1 because none of the moves included
    //contain the previous location
    if(moves.size() > 1)
        backtrace.push(currLocation);


}