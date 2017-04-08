#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <dlfcn.h>

#include "playergame.h"
#include "./Interfaces/player.h"

template<class PlayerType>
class PlayerLoader
{
    typedef void playerDestroy_t(PlayerType*);
    typedef PlayerType* playerCreate_t();

    struct playerHandle
    {
        //Shared library pointers
        PlayerType* ptr;
        playerCreate_t* createFunc;
        playerDestroy_t* destroyFunc;
        void* library;
    };

    std::vector<playerHandle> _players;
    PlayerGame<PlayerType>* _game;
public:
    PlayerLoader(PlayerGame<PlayerType>* game);
    ~PlayerLoader();

    void unloadPlayers();
    void loadPlayers(std::string dir);
};


template<class PlayerType>
PlayerLoader<PlayerType>::PlayerLoader(PlayerGame<PlayerType> *game) : _game(game)
{

}

template<class PlayerType>
PlayerLoader<PlayerType>::~PlayerLoader()
{
    unloadPlayers();
}

template<class PlayerType>
void PlayerLoader<PlayerType>::unloadPlayers()
{
    for(playerHandle& p : _players)
    {
        _game->removePlayer(p.ptr);
        p.destroyFunc(p.ptr);
        dlclose(p.library);
    }
}

template<class PlayerType>
void PlayerLoader<PlayerType>::loadPlayers(std::string dir)
{
    DIR *dp;
    struct dirent *dirp;
    std::cout << "Adding players from " << dir << std::endl;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return;
    }

    while ((dirp = readdir(dp)) != nullptr) {
        std::string fileName = std::string(dirp->d_name);
        if(fileName.find(".so") != std::string::npos)
        {
            playerHandle newPlayer;

            std::string path = dir + "/" + fileName;
            std::cout << "Loading player from" << path << std::endl;
            newPlayer.library = dlopen(path.c_str(), RTLD_LAZY);
            if(newPlayer.library == nullptr)
            {
                std::cout << "Unable to open library" << std::endl;
                continue;
            }

            dlerror();
            bool failed = false;

            newPlayer.createFunc = (playerCreate_t*) dlsym(newPlayer.library, "createPlayer");
            const char* err = dlerror();
            if(err)
            {
                std::cout << "Unable to load createPlayer function: " << err << std::endl;
                failed = true;
            }

            dlerror();
            newPlayer.destroyFunc = (playerDestroy_t*) dlsym(newPlayer.library, "destroyPlayer");
            err = dlerror();
            if(err)
            {
                std::cout << "Unable to load destroyPlayer function: " << err << std::endl;
                failed = true;
            }

            newPlayer.ptr = newPlayer.createFunc();
            if(newPlayer.ptr == nullptr)
            {
                std::cout << "Failed to create player" << std::endl;
                failed = true;
            }

            if(failed)
            {
                dlclose(newPlayer.library);
            }
            else
            {
                _game->addPlayer(newPlayer.ptr);
                std::cout << "Added player " << newPlayer.ptr->playerName() << std::endl;
                _players.push_back(newPlayer);
            }
        }
    }
    closedir(dp);
}

#endif // MAZEGAME_H
