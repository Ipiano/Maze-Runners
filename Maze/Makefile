# Makefile for maze runner project
# Author: Andrew Stelter

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
LINK = g++

# Turn on optimization and warnings, use c++11:
CFLAGS = -std=c++11 -Wall -O
CXXFLAGS = $(CFLAGS)

PLAYEROBJS = ./Player/randomPlayer.o ./Player/rightHandPlayer.o ./Player/sointerface.o \
				./Player/jumperPlayer.o
GAMEOBJS = ./Mazes/basicmover.o \
			./Mazes/dfsgenerator.o ./Mazes/squarepartitioner.o main.o 

# Math library
LIBS = -lm -ldl

#-----------------------------------------------------------------------
# Specific targets:

all: game player.so

%.o: %.cpp
	$(LINK) -fPIC -c -Wall $^ -o $@

player.so: $(PLAYEROBJS)
	mkdir Players; $(LINK) -shared -Wl,-soname,./Players/libplayer.so \
	-o ./Players/libplayer.so $(PLAYEROBJS) -lc

game: $(GAMEOBJS)
	$(LINK) -o $@ $(GAMEOBJS) $(LIBS)

debug: CXXFLAGS += -g
debug: all

clean:
	find . -type f -name '*.o' -exec rm {} +
	find . -type f -name '*.so' -exec rm {} +
	rm game

remake: clean all
