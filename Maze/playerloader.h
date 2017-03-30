#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <string>
#include <vector>
#include <string>

#include "mazerunner.h"
#include "./Player/player.h"

typedef void playerDestroy_t(Player*);
typedef Player* playerCreate_t();

class PlayerLoader
{
    struct playerHandle
    {
        //Shared library pointers
        Player* ptr;
        playerCreate_t* createFunc;
        playerDestroy_t* destroyFunc;
        void* library;
    };

    std::vector<playerHandle> _players;
    MazeRunner* _maze;
public:
    PlayerLoader(MazeRunner* maze);
    ~PlayerLoader();

    void unloadPlayers();
    void loadPlayers(std::string dir);
};

#endif // MAZEGAME_H
