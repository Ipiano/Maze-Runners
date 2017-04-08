#include "advancedmover.h"

#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

MazePoint AdvancedMover::closestPointToExit(MazePoint current, maze<AdvancedMapTile>& m)
{
    queue<MazePoint> bfs;
    unordered_map<int, unordered_map<int, int>> distances;
    int currDist = 1;
    int frontSize = 1;
    bfs.push(MazePoint{m.exit.x, m.exit.y});
    while(bfs.size())
    {
        int nextFront = 0;
        for(int i=0; i<frontSize; i++)
        {
            MazePoint next = bfs.front();
            bfs.pop();

            //If we reach the player location, check which of the four directions we came from
            if(next.x == current.x && next.y == current.y)
            {
                if(distances[next.x-1][next.y] == currDist-1) return MazePoint{next.x-1, next.y};
                if(distances[next.x+1][next.y] == currDist-1) return MazePoint{next.x+1, next.y};
                if(distances[next.x][next.y-1] == currDist-1) return MazePoint{next.x, next.y-1};
                if(distances[next.x][next.y+1] == currDist-1) return MazePoint{next.x, next.y+1};

                //Should only happen if they use luck from in a walls only room
                cout << "You are REALLY unlucky!" << endl;;
                return current;
            }

            distances[next.x][next.y] = currDist;
            AdvancedMapTile t = m.at(next.x, next.y);
            if(t.exits & (unsigned int)AdvancedMapTile::Direction::NORTH)
            {
                nextFront++;
                bfs.push(MazePoint{next.x, next.y-1});
            }
            if(t.exits & (unsigned int)AdvancedMapTile::Direction::SOUTH)
            {
                nextFront++;
                bfs.push(MazePoint{next.x, next.y+1});
            }
            if(t.exits & (unsigned int)AdvancedMapTile::Direction::EAST)
            {
                nextFront++;
                bfs.push(MazePoint{next.x+1, next.y});
            }
            if(t.exits & (unsigned int)AdvancedMapTile::Direction::WEST)
            {
                nextFront++;
                bfs.push(MazePoint{next.x-1, next.y});
            }
        }
        currDist++;
        frontSize = nextFront;
    }

    cout << "You are unlucky!" << endl;;
    return current;
}


void AdvancedMover::performPlayerPendingMove(AdvancedPlayerData& playerData,
                                  maze<AdvancedMapTile>& m)
{
    bool playerMoved = false;
    switch(playerData.moveInProgress.attemptedMove)
    {
        case AdvancedPlayerMove::Move::NOOP: return;

        case AdvancedPlayerMove::Move::MOVETO:
            playerData.x += playerData.moveInProgress.destination.x;
            playerData.y += playerData.moveInProgress.destination.y;
            if(abs(playerData.moveInProgress.destination.x) > 0 && abs(playerData.moveInProgress.destination.y))
                playerData.willLeft--;

            playerMoved = true;
        break;

        case AdvancedPlayerMove::Move::WALLBREAK:
            m.at(playerData.x, playerData.y).exits |= (unsigned char)playerData.moveInProgress.dir;
            playerData.wallBreaksLeft--;
            goto breakorphase;
        case AdvancedPlayerMove::Move::WALLPHASE:
            playerData.wallPhaseLeft--;
breakorphase:
            switch(playerData.moveInProgress.dir)
            {
                case AdvancedMapTile::Direction::NORTH:
                    playerData.y--;
                    break;
                case AdvancedMapTile::Direction::SOUTH:
                    playerData.y++;
                    break;
                case AdvancedMapTile::Direction::WEST:
                    playerData.x--;
                    break;
                case AdvancedMapTile::Direction::EAST:
                    playerData.x++;
                    break;
            }
            playerMoved = true;
        break;
        case AdvancedPlayerMove::Move::STICKYBOMB:
            playerData.stickyBombs--;
            m.at(playerData.x, playerData.y).hasStickyBomb = true;
        break;
        case AdvancedPlayerMove::Move::LUCK:
        {
            MazePoint moveto = closestPointToExit(MazePoint{playerData.x, playerData.y}, m);
            playerData.x = moveto.x;
            playerData.y = moveto.y;
            playerData.luckLeft--;
            playerMoved = true;
        }
        break;
    }

    //Check if player stepped on a sticky bomb
    //If so, change the ticksLeftForCurrentMove so they have to wait to move
    if(playerMoved && m.at(playerData.x, playerData.y).hasStickyBomb)
    {
        playerData.ticksLeftForCurrentMove = 10;
        playerData.moveInProgress = defaultMove();
    }
}

bool AdvancedMover::isValidMove(AdvancedPlayerData& playerData, 
                     const AdvancedPlayerMove& move,
                     maze<AdvancedMapTile>& m)
{
    switch(move.attemptedMove)
    {
        case AdvancedPlayerMove::Move::NOOP: return true;
        case AdvancedPlayerMove::Move::MOVETO:
        {
            AdvancedMapTile currTile = m.at(playerData.x, playerData.y);

            //Check if they're trying to move any of the four cardinal directions
            if(move.destination.x == 0 && move.destination.y == 1 && 
               (currTile.exits & (unsigned int) AdvancedMapTile::Direction::SOUTH) > 0) return true;
               
            if(move.destination.x == 0 && move.destination.y == -1 && 
               (currTile.exits & (unsigned int) AdvancedMapTile::Direction::NORTH) > 0) return true;

            if(move.destination.x == 1 && move.destination.y == 0 && 
               (currTile.exits & (unsigned int) AdvancedMapTile::Direction::EAST) > 0) return true;

            if(move.destination.x == -1 && move.destination.y == 0 && 
               (currTile.exits & (unsigned int) AdvancedMapTile::Direction::WEST) > 0) return true;

            //Check if trying to teleport to a previously visited location
            if(_visited[playerData.id][playerData.x+move.destination.x][playerData.y+move.destination.y]
               && playerData.willLeft > 0) return true;

            return false;
        }
        case AdvancedPlayerMove::Move::WALLBREAK:
        {
            AdvancedMapTile currTile = m.at(playerData.x, playerData.y);
            if((currTile.exits & (unsigned char)move.dir) == 0)
                return playerData.wallBreaksLeft > 0;
            
            return false;
        }
        case AdvancedPlayerMove::Move::WALLPHASE:
        {
            AdvancedMapTile currTile = m.at(playerData.x, playerData.y);
            if((currTile.exits & (unsigned char)move.dir) == 0)
                return playerData.wallPhaseLeft > 0;
            
            return false;
        }
        case AdvancedPlayerMove::Move::STICKYBOMB:
        {
            if(playerData.stickyBombs > 0) return true;
            return false;
        }
        case AdvancedPlayerMove::Move::LUCK:
        {
            if(playerData.luckLeft > 0) return true;
            return false;
        }
    }
    return false;
}

//Right now, all moves take same number of ticks
int AdvancedMover::moveLength(AdvancedPlayerData& playerData, 
                const AdvancedPlayerMove& move,
                maze<AdvancedMapTile>& m)
{
    return playerData.ticksPerTurn;
}


//Assign move in moveInProgress
//Assign amount of time ticks the move takes
void AdvancedMover::setupNextPlayerMove(AdvancedPlayerData& playerData,
                        const AdvancedPlayerMove& move,
                        maze<AdvancedMapTile>& m)
{
    if(isValidMove(playerData, move, m))
    {
        playerData.moveInProgress = move;
        playerData.ticksLeftForCurrentMove = moveLength(playerData, move, m);
    }
    else
    {
        playerData.moveInProgress = defaultMove();
        playerData.ticksLeftForCurrentMove = 0;
    }
}

void AdvancedMover::movePlayer(AdvancedPlayerData& playerData,
                    const AdvancedPlayerMove& move,
                    maze<AdvancedMapTile>& m)
{
    //Tick down to 1, and perform the move
    //Then next turn see what their next move is
    //and set the ticks left again
    if(playerData.ticksLeftForCurrentMove == 1)
        performPlayerPendingMove(playerData, m);
    else if(playerData.ticksLeftForCurrentMove < 1)
        setupNextPlayerMove(playerData, move, m);
    playerData.ticksLeftForCurrentMove--;
}