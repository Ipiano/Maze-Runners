# Makefile for drawing library
# Author: Andrew Stelter

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
LINK = g++

# Turn on optimization and warnings, use c++11:
CFLAGS = -std=c++11 -Wall -O
CXXFLAGS = $(CFLAGS)

IODIR = ./IOInterfaces
WIDGDIR = ./IOInterfaces/Widgets
LAYDIR = ./IOInterfaces/Widgets/Layouts
GLUTDIR = ./GlutInterfaces

INTERFACE =$(IODIR)/ScreenHandler.o
WIDGET = $(WIDGDIR)/Point.o $(LAYDIR)/Layout.o $(LAYDIR)/StaticLayout.o
GLUT = $(GLUTDIR)/GlutInputSignaler.o $(GLUTDIR)/GlutScreenCanvas.o

#-----------------------------------------------------------------------
# Specific targets:

all: libdraw.a

libdraw.a: $(INTERFACE) $(WIDGET) $(GLUT)
	ar rvs $@ $(INTERFACE) $(WIDGET) $(GLUT)

debug: CXXFLAGS += -g
debug: all

clean:
	find . -type f -name '*.o' -exec rm {} +
	rm -f *~ libdraw.a

remake: clean all
