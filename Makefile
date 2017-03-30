# Makefile for animatable maze
# Author: Andrew Stelter

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
LINK = g++

MAZEDIR = ./Maze
MAZESDIR = $(MAZEDIR)/Mazes
PLAYERDIR = $(MAZEDIR)/Player

ALGODIR = ./AnimAlgoLib

DRAWDIR = ./DrawLib
IODIR = $(DRAWDIR)/IOInterfaces
WIDGDIR = $(IODIR)/Widgets
LAYDIR = $(WIDGDIR)/Layouts
GLUTDIR = $(DRAWDIR)/GlutInterfaces

GAMEOBJS = $(MAZESDIR)/basicmover.o $(MAZESDIR)/dfsgenerator.o $(MAZEDIR)/playerloader.o \
		   $(MAZEDIR)/mazerunner.o $(MAZESDIR)/squarepartitioner.o
ANIMOBJS = animatedmaze.o mazevisualizer.o main.o

# Turn on optimization and warnings, use c++11:
CFLAGS = -std=c++11 -Wall -O -I$(ALGODIR) -I$(IODIR) -I$(WIDGDIR) -I$(GLUTDIR) -I$(LAYDIR)
CXXFLAGS = $(CFLAGS)

# Math library
GL_LIBS = -lglut -lGLU -lGL
LIBS = -lm -ldl -lanimalgo -ldraw
LIBDIRS = -L$(DRAWDIR) -L$(ALGODIR)
MAKETARGS = all

#-----------------------------------------------------------------------
# Specific targets:

all: visual

libanimalgo.a: 
	cd $(ALGODIR) && $(MAKE) $(MAKETARGS)
	
libdraw.a:
	cd $(DRAWDIR) && $(MAKE) $(MAKETARGS)

visual: libanimalgo.a libdraw.a $(GAMEOBJS) $(ANIMOBJS)
	$(LINK) -o $@ $(GAMEOBJS) $(ANIMOBJS) $(LIBDIRS) $(GL_LIBS) $(LIBS)

debug: CXXFLAGS += -g
debug: MAKETARGS = debug
debug: all

clean:
	find . -type f -name '*.o' -exec rm {} +
	cd $(DRAWDIR) && $(MAKE) clean
	cd $(ALGODIR) && $(MAKE) clean
	rm -f visual

remake: clean all
