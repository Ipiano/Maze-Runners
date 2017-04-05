# Makefile for maze runner project
# Author: Andrew Stelter

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
LINK = g++

# Turn on optimization and warnings, use c++11:
CFLAGS = -std=c++11 -Wall -O
CXXFLAGS = $(CFLAGS)

PLAYEROBJS = randomPlayer.o rightHandPlayer.o jumperPlayer.o

PLAYERSOS = $(PLAYEROBJS:.o=.so)

GAMEOBJS = ./Mazes/basicmover.o \
			./Mazes/dfsgenerator.o ./Mazes/squarepartitioner.o main.o 

# Math library
LIBS = -lm -ldl

VPATH = Player

#-----------------------------------------------------------------------
# Specific targets:

all: game $(PLAYERSOS)

%.o: %.cpp
	$(LINK) -fPIC -c $(CXXFLAGS) $^ -o $@

%.so: %.o
	mkdir -p Players
	$(LINK) -shared -Wl,-soname,./Players/$@ -o ./Players/$@ $^ -lc

game: $(GAMEOBJS)
	$(LINK) -o $@ $(GAMEOBJS) $(LIBS)

debug: CXXFLAGS += -g
debug: all

clean:
	find . -type f -name '*.o' -exec rm {} +
	find . -type f -name '*.so' -exec rm {} +
	rm game

remake: clean all
