# Makefile for maze runner project
# Author: Andrew Stelter

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
LINK = g++

# Turn on optimization and warnings, use c++11:
CFLAGS = -std=c++11 -Wall -O
CXXFLAGS = $(CFLAGS)

PLAYEROBJS = randomPlayer.o rightHandPlayer.o jumperPlayer.o lucky.o

PLAYERSOS = $(PLAYEROBJS:.o=.so)

BASICGAMEOBJS = \
   ./Mazes/Basic/basicmover.o \
   ./Mazes/Basic/basicrules.o \
   ./Mazes/Basic/dfsgenerator.o \
   ./Mazes/Basic/squarepartitioner.o

ADVANCEDGAMEOBJS = \
   ./Mazes/Advanced/advancedmover.o \
   ./Mazes/Advanced/advancedrules.o \
   ./Mazes/Advanced/advancedgenerator.o \
   ./Mazes/Advanced/advancedpartitioner.o

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

game: $(BASICGAMEOBJS) $(ADVANCEDGAMEOBJS) main.o
	$(LINK) -o $@ $(GAMEOBJS) $(ADVANCEDGAMEOBJS) main.o $(LIBS)

debug: CXXFLAGS += -g
debug: all

clean:
	find . -type f -name '*.o' -exec rm {} +
	find . -type f -name '*.so' -exec rm {} +
	rm game

remake: clean all

%.o: %.h
