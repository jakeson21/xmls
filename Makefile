# the compiler to use.
CC=g++
RM=\rm *.o Demo
src =$(wildcard *.cpp)
OBJS =$(src:.cpp=.o)
LDFLAGS =-L/usr/lib/
INC=-I/usr/informix/incl/c++ -I/opt/informix/incl/public
EXECUTABLE=Demo

# options I'll pass to the compiler.
CXXFLAGS =-Wall -c
DEBUG    =-Wall -g -c

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE)

$(EXECUTABLE).o:
	$(CC) $(CXXFLAGS) $(EXECUTABLE).cpp
	
tinyxml2.o: tinyxml2.h
	$(CC) $(CXXFLAGS) tinyxml2.cpp

XMLSerialization.o: XMLSerialization.h
	$(CC) $(CXXFLAGS) XMLSerialization.cpp

debug: CXXFLAGS=$(DEBUG)
debug: all


.PHONY: clean
clean:
	rm -f $(OBJS) Demo
