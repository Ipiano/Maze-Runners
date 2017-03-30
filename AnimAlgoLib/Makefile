# Makefile for drawing library
# Author: Andrew Stelter

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
LINK = g++

# Turn on optimization and warnings, use c++11:
CFLAGS = -std=c++11 -Wall -O
CXXFLAGS = $(CFLAGS)

ALGO = ./IteratedAlgo.o

#-----------------------------------------------------------------------
# Specific targets:

all: libanimalgo.a

libanimalgo.a: $(ALGO)
	ar rvs $@ $(ALGO)

debug: CXXFLAGS += -g
debug: all

clean:
	find . -type f -name '*.o' -exec rm {} +
	rm -f *~ libanimalgo.a

remake: clean all
