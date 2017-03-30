#include "GlutScreenCanvas.h"

#include<iostream>

using namespace std;

GlutScreenCanvas::GlutScreenCanvas()
{

}

void GlutScreenCanvas::init(int& argc, char** argv, const string& windowName, const unsigned int& width, const unsigned int& height)
{
    glutInit(&argc, argv);

    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );	        // 32-bit graphics and double buffering

    _width = width;
    _height = height;

    glutInitWindowSize( _width, _height );	    // initial window size
    glutInitWindowPosition( 100, 50 );			    // initial window  position
    _window = glutCreateWindow( windowName.c_str() );			    // window title

    glClearColor( 0.0, 0.0, 0.0, 0.0 );			    // use black for glClear command
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

}

void GlutScreenCanvas::resize(const unsigned int& width, const unsigned int& height)
{
    _width = width;
    _height = height;

    // project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );		// use an orthographic projection
    glLoadIdentity();				    // initialize transformation matrix
    gluOrtho2D( 0.0, _width, 0.0, _height );		// make OpenGL coordinates
    glViewport( 0, 0, _width, _height );			// the same as the screen coordinates
}

void GlutScreenCanvas::redraw()
{
    glClear( GL_COLOR_BUFFER_BIT ); 

    signalDraw(this);
    glFlush();

    glutSwapBuffers();
}

void GlutScreenCanvas::drawBitmap(const unsigned int& width, const unsigned int& height, const unsigned int& x, const unsigned int& y, const unsigned char* bits) const
{
    glRasterPos2i( x, y );
    glDrawPixels( width, height, GL_RGB, GL_UNSIGNED_BYTE, bits);
}
