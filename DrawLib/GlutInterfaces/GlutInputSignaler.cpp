#include "GlutInputSignaler.h"

#include <GL/freeglut.h>

GlutInputSignaler* GlutInputSignaler::activeHandler = nullptr;

GlutInputSignaler::GlutInputSignaler()
{

}

GlutInputSignaler::~GlutInputSignaler()
{
    if(this == GlutInputSignaler::activeHandler)
        GlutInputSignaler::activeHandler = nullptr;
}

void GlutInputSignaler::setAsActiveHandler()
{
    GlutInputSignaler::activeHandler = this;
    glutDisplayFunc(&GlutInputSignaler::redraw_stat);
    glutReshapeFunc(&GlutInputSignaler::reshape_stat);
    glutIdleFunc(&GlutInputSignaler::idle_stat);
    glutKeyboardFunc(&GlutInputSignaler::keydown_stat);
    glutMouseFunc(&GlutInputSignaler::mouseClick_stat);
}

//Static calls that can be set as
//callbacks for glut
void GlutInputSignaler::redraw_stat( void )
{
    if(nullptr != GlutInputSignaler::activeHandler)
        GlutInputSignaler::activeHandler->signalRedisplay();
}

void GlutInputSignaler::reshape_stat( int w, int h )
{
    if(nullptr != GlutInputSignaler::activeHandler)
        GlutInputSignaler::activeHandler->signalResize(w, h);
}

void GlutInputSignaler::keydown_stat( unsigned char key, int x, int y )
{
    if(nullptr != GlutInputSignaler::activeHandler)
        GlutInputSignaler::activeHandler->signalKeyPress(key, x, y);
}

void GlutInputSignaler::mouseClick_stat(int button_raw, int state_raw, int x, int y)
{
    MouseButton button;
    ButtonState state;

    //Normalize button input
    switch(button_raw)
    {
        case GLUT_RIGHT_BUTTON: button = MouseButton::RIGHT; break;
        case GLUT_MIDDLE_BUTTON: button = MouseButton::MIDDLE; break;
        case GLUT_LEFT_BUTTON:
        default:
            button = MouseButton::LEFT; break;
    }

    //Normalize state input
    switch(state_raw)
    {
        case GLUT_UP: state = ButtonState::UP; break;
        case GLUT_DOWN:
        default:
            state = ButtonState::DOWN; break;
    }

    if(nullptr != GlutInputSignaler::activeHandler)
        GlutInputSignaler::activeHandler->signalMouseClick(x, y, button, state);
}

void GlutInputSignaler::idle_stat()
{
    if(nullptr != GlutInputSignaler::activeHandler)
        GlutInputSignaler::activeHandler->signalIdle();
}
