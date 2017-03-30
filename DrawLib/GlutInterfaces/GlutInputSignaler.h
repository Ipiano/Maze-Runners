#ifndef GLUTINPUTSIGNALER_H
#define GLUTINPUTSIGNALER_H

#include "../IOInterfaces/InputSignaler.h"

class GlutInputSignaler : public InputSignaler
{
    static GlutInputSignaler* activeHandler;

    //Static calls that can be set as
    //callbacks for glut
    static void redraw_stat( void );
    static void reshape_stat( int w, int h );
    static void keydown_stat( unsigned char key, int x, int y );
    static void mouseClick_stat(int button_raw, int state_raw, int x, int y);
    static void idle_stat();

public:
    GlutInputSignaler();
    ~GlutInputSignaler();
    void setAsActiveHandler();
    static void removeActiveHandler(){activeHandler = nullptr;}
};

#endif // GLUTINPUTSIGNALER_H
