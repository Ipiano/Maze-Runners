#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "../InputSignaler.h"
#include "../IOConst.h"

class Clickable : public virtual MouseClickSignaler
{
    long long _clickCallback;
    MouseClickSignaler* _input = nullptr;

public:
    virtual void setClickInput(MouseClickSignaler* input)
    {
        if(_input != nullptr)
            _input->removeMouseClickReceiver(_clickCallback);

        if(input != nullptr)
            _clickCallback = input->addMouseClickReceiver(this, &Clickable::processClick);
        _input = input;
    }

protected:
    virtual void processClick(const double &x, const double &y, const MouseButton &button, const ButtonState &state){};
};

#endif // CLICKABLE_H
