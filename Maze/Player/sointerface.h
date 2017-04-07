#ifndef SOINTERFACE_H
#define SOINTERFACE_H

#include "../Interfaces/attributePlayer.h"

extern "C" AttributePlayer* createPlayer();

extern "C" void destroyPlayer(AttributePlayer* p);

#endif // SOINTERFACE_H
