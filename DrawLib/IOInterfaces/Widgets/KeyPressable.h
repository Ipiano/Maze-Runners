#ifndef KEYPRESSABLE_H
#define KEYPRESSABLE_H

#include "../InputSignaler.h"

class KeyPressable : public virtual KeyPressSignaler
{
    long long _keyCallback;
    KeyPressSignaler* _input = nullptr;

public:
    virtual void setKeyPressInput(KeyPressSignaler* input)
    {
        if(_input != nullptr)
            _input->removeKeyPressReceiver(_keyCallback);

        if(input != nullptr)
            _keyCallback = input->addKeyPressReceiver(this, &KeyPressable::processKeyPress);

        _input = input;
    }

protected:
    void processKeyPress(const unsigned char& key, const double &x, const double &y){};
};

#endif // KEYPRESSABLE_H
