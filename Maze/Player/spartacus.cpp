#include "spartacus.h"

#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

MazePoint operator + (const MazePoint& l, const MazePoint& r)
{
    return MazePoint{l.x + r.x, l.y + r.y};
}

MazePoint operator - (const MazePoint& l, const MazePoint& r)
{
    return MazePoint{l.x - r.x, l.y - r.y};
}

MazePoint operator != (const MazePoint& l, const MazePoint& r)
{
    return l.x != r.x || l.y != r.y;
}

vector<MazePoint> Bresenham(MazePoint start, MazePoint end)
{
    int deltax = end.x - start.x;
    int deltay = end.y - start.y;

    vector<MazePoint> line;

    //Handle trivial cases
    if(deltax == 0)
    {
        int ydir = deltay/abs(deltay);
        for(int i=start.y; i != end.y; i+=ydir)
            line.push_back(MazePoint(start.x, i));
        return line;
    }

    if(deltay == 0)
    {
        int xdir = deltax/abs(deltax);
        for(int i=start.x; i != end.x; i+=xdir)
            line.push_back(MazePoint(i, start.y));
        return line;
    }

    int xdir = deltax/abs(deltax);
    int ydir = deltay/abs(deltay);

    double deltaerr = abs((double)deltay / deltax);
    double error = deltaerr - 0.5;
    MazePoint curr = start;

    MazePoint diffReg, diffAdj;
    if(abs(deltay) > abs(deltax))
    {
        diffReg = MazePoint(0, ydir);
        diffAdj = MazePoint(xdir, 0);
    }
    else
    {
        diffReg = MazePoint(xdir, 0);
        diffAdj = MazePoint(0, ydir);
    }

    for(int i=0; i<max(abs(deltay), abs(deltax))+1; i++)
    {
        line.push_back(curr);
        error += deltaerr;
        if(error >= 0.5)
        {
            curr = curr + diffAdj;
            error -= 1;
        }
        curr = curr + diffReg;
    }

    return line;
}

void Spartacus::setMazeSettings(const MazeSettings& settings)
{
    MazePoint curr(0, 0);
    MazePoint target(settings.exit_x, settings.exit_y);

    targetLine = Bresenham(curr, target);
    targetLine.pop_front();

    location = MazePoint(0,0);
    lastMove = AdvancedPlayerMove();
    firstTurn = true;
    world.clear();
    visited.clear();
    wallBreaks = 3;
}

void Spartacus::bfsDeadEnds(const MazePoint& start)
{

}

void Spartacus::bfsExit(const MazePoint& start)
{

}

std::vector<MazePoint> Spartacus::checkPathToTargetLine()
{
    
}

AdvancedPlayerMove bookkeeping(const AdvancedMapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y)
{
    AdvancedPlayerMove out;
    AdvancedMapTile currentTile = surroundings[area_width*loc_y + loc_x];
    if(!firstTurn && lastTile.uid != currentTile.uid)
    {
        if(lastMove.attemptedMove == AdvancedPlayerMove::Move::MOVETO)
            location = location + lastMove.destination;
        else if(lastMove.attemptedMove == AdvancedPlayerMove::Move::WALLBREAK ||
                lastMove.attemptedMove == AdvancedPlayerMove::Move::WALLPHASE)
            switch(lastMove.dir)
            {
                case AdvancedMapTile::Direction::NORTH:
                    location.y -= 1; break;
                case AdvancedMapTile::Direction::SOUTH:
                    location.y += 1; break;
                case AdvancedMapTile::Direction::WEST:
                    location.x -= 1; break;
                case AdvancedMapTile::Direction::EAST:
                    location.x += 1; break;
            }
    }

    lastTile = currentTile;
    firstTurn = false;
    lastMove = AdvancedPlayerMove();

    visited[location.x][location.y] = true;

    auto iter = surroundings;
    for(int i=0; i<area_height; i++)
    {
        for(int j=0; j<area_width; j++)
        {
            if(iter->exits != 0)
            {
                world[j][i] = *iter;
                bfsDeadEnds(MazePoint(j, i));
                bfsExit(MazePoint(j, i));
            }
        }
    }

    //Check if we can move onto (or next to) the exit path
    out = moveOntoExitPath();
    if(out.attemptedMove != AdvancedPlayerMove::Move::NOOP) return out;

    //See if we know how to get to somewhere further on the target line
    vector<MazePoint> newPath = checkPathToTargetLine();
    if(newPath.size() > 0) plannedPath = newPath;

    //If we previously planned a path, follow along it
    if(plannedPath.size())
    {
        out.attemptedMove = AdvancedPlayerMove::Move::MOVETO;
        out.destination = location-plannedPath.front();
        plannedPath.pop_front();
    }

    return out;
}

AdvancedPlayerMove Spartacus::move(const AdvancedMapTile* surroundings,                //Const pointer to local area
                            const uint& area_width, const uint& area_height,    //Size of local area
                            const uint& loc_x, const uint& loc_y)
{
    AdvancedPlayerMove out = bookkeeping(surroundings, area_width, area_height, loc_x, loc_y);
    if(out.attemptedMove != AdvancedPlayerMove::Move::NOOP) 
    {
        lastMove = out;
        return out;
    }

    return out;
}













/*
ostream& operator <<(ostream& out, queue<MazePoint> q)
{
    while(q.size())
    {
        out << "(" << q.front().x << ", " << q.front().y << ") ";
        q.pop();
    }
    return out;
}

int main()
{
    cout << "Trivial cases..." << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(0, 10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(0, -10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(10, 0)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(-10, 0)) << endl;

    cout << endl << "45 degrees..." << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(10, 10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(10, -10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(-10, -10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(-10, 10)) << endl;

    cout << endl << "Other..." << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(10, 5)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(5, 10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(-5, 10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(-10, 5)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(-10, -5)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(-5, -10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(5, -10)) << endl;
    cout << Bresenham(MazePoint(0, 0), MazePoint(10, -5)) << endl;

    cout << Bresenham(MazePoint(0, 0), MazePoint(11, 7)) << endl;
}
*/