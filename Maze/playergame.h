#ifndef _PLAYER_GAME_H
#define _PLAYER_GAME_H

template<class PlayerType>
class PlayerGame
{
public:
    virtual void addPlayer(PlayerType* p) = 0;
    virtual void removePlayer(PlayerType* p) = 0;
};

#endif