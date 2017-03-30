#ifndef INPUTSIGNALER_H
#define INPUTSIGNALER_H

#include <unordered_map>
#include <functional>

#include "IOConst.h"

#define SignalClass(Signal, FuncReturn, FuncSig, FuncArgs, FuncCall, BindCall)\
class Signal##Signaler\
{\
public:\
    typedef std::function<FuncReturn FuncArgs> Signal##Callback;\
    \
private:\
    unsigned long long _nextId = 0; \
    std::unordered_map<unsigned long long, Signal##Callback> _callbacks;\
    \
public:\
    void signal##Signal FuncArgs\
    {\
        for(auto& p : _callbacks)\
            p.second FuncCall; \
    }\
    \
    unsigned long long add##Signal##Receiver (const Signal##Callback& cb)\
    {\
        _callbacks[_nextId] = cb;\
        return _nextId++;\
    }\
    \
    template<class T, class Func>\
    unsigned long long add##Signal##Receiver(T* obj, Func cb)\
    {\
        using namespace std::placeholders;\
        return add##Signal##Receiver (std::bind BindCall );\
    }\
    \
    void remove##Signal##Receiver (const unsigned long long& cbId)\
    {\
        _callbacks.erase(cbId); \
    }\
};\

SignalClass(MouseClick, void, (const int&, const int&, const MouseButton&, const ButtonState&), \
            (const int& x, const int& y, const MouseButton& button, const ButtonState& state), \
            (x, y, button, state), (cb, obj, _1, _2, _3, _4))

SignalClass(KeyPress, void, (const unsigned char&, const int&, const int&), \
            (const unsigned char& key, const int& x, const int& y), \
            (key, x, y), (cb, obj, _1, _2, _3))

SignalClass(Idle, void, (void), (void), (), (cb, obj))
SignalClass(Redisplay, void, (void), (void), (), (cb, obj))
SignalClass(Resize, void, (const int&, const int &), (const int& width, const int& height),\
            (width, height), (cb, obj, _1, _2))

class DrawingCanvas;
SignalClass(Draw, void, (const DrawingCanvas*), (const DrawingCanvas* canvas), (canvas), (cb, obj, _1));

class InputSignaler : public MouseClickSignaler, public KeyPressSignaler,
                      public IdleSignaler, public RedisplaySignaler, public ResizeSignaler
{
};

#endif // INPUTSIGNALER_H
