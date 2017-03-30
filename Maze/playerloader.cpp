#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <dlfcn.h>

#include "playerloader.h"

using namespace std;

PlayerLoader::PlayerLoader(MazeRunner *maze) : _maze(maze)
{

}

PlayerLoader::~PlayerLoader()
{
    unloadPlayers();
}

void PlayerLoader::unloadPlayers()
{
    for(playerHandle& p : _players)
    {
        _maze->removePlayer(p.ptr);
        p.destroyFunc(p.ptr);
        dlclose(p.library);
    }
}

void PlayerLoader::loadPlayers(string dir)
{
    DIR *dp;
    struct dirent *dirp;
    cout << "Adding players from " << dir << endl;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return;
    }

    while ((dirp = readdir(dp)) != nullptr) {
        string fileName = string(dirp->d_name);
        if(fileName.find(".so") != string::npos)
        {
            playerHandle newPlayer;

            string path = dir + "/" + fileName;
            cout << "Loading player from" << path << endl;
            newPlayer.library = dlopen(path.c_str(), RTLD_LAZY);
            if(newPlayer.library == nullptr)
            {
                cout << "Unable to open library" << endl;
                continue;
            }

            dlerror();
            bool failed = false;

            newPlayer.createFunc = (playerCreate_t*) dlsym(newPlayer.library, "createPlayer");
            const char* err = dlerror();
            if(err)
            {
                cout << "Unable to load createPlayer function: " << err << endl;
                failed = true;
            }

            dlerror();
            newPlayer.destroyFunc = (playerDestroy_t*) dlsym(newPlayer.library, "destroyPlayer");
            err = dlerror();
            if(err)
            {
                cout << "Unable to load destroyPlayer function: " << err << endl;
                failed = true;
            }

            newPlayer.ptr = newPlayer.createFunc();
            if(newPlayer.ptr == nullptr)
            {
                cout << "Failed to create player" << endl;
                failed = true;
            }

            if(failed)
            {
                dlclose(newPlayer.library);
            }
            else
            {
                _maze->addPlayer(newPlayer.ptr);
                cout << "Added player " << newPlayer.ptr->playerName() << endl;
                _players.push_back(newPlayer);
            }
        }
    }
    closedir(dp);
}
