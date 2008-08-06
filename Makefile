
CPP = g++
CLINKER = gcc
CFLAGS=-gdwarf-2 -Wall 
CXXFLAGS = -g3 -O0

SOURCES=test01.cpp test02.cpp cellnode.cpp simclock.cpp rootsim.cpp
HEADER=cellnode.h simclock.h rootsim.h
OBJECTS=$(SOURCES:.cpp=.o)

all: \
	Diffusion \
	Division

test: all 
	Diffusion  
	Division  
 

Diffusion: test01.o cellnode.o simclock.o rootsim.o
	$(CPP) -o Diffusion $(CXXFLAGS) test01.o cellnode.o simclock.o rootsim.o

Division: test02.o cellnode.o simclock.o rootsim.o
	$(CPP) -o Division $(CXXFLAGS) test02.o cellnode.o simclock.o rootsim.o

test01.o : test01.cpp cellnode.h simclock.h rootsim.h
	$(CPP) -c $(CFLAGS) test01.cpp cellnode.h simclock.h rootsim.h

test02.o : test02.cpp cellnode.h simclock.h rootsim.h
	$(CPP) -c $(CFLAGS) test02.cpp cellnode.h simclock.h rootsim.h

cellnode.o : cellnode.cpp cellnode.h rootsim.h
	$(CPP) -c $(CFLAGS) cellnode.cpp cellnode.h rootsim.h

simclock.o : simclock.cpp simclock.h rootsim.h
	$(CPP) -c $(CFLAGS) simclock.cpp simclock.h rootsim.h

rootsim.o : rootsim.cpp rootsim.h
	$(CPP) -c $(CFLAGS) rootsim.cpp rootsim.h

.PHONY: clean
clean:
	rm -fr Division Diffusion $(OBJECTS)
