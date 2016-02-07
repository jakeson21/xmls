# the compiler to use.
CC=g++
RM=\rm *.o Demo
src =$(wildcard *.cpp)
OBJS =$(src:.cpp=.o) tinyxml2.o
LDFLAGS =-L/usr/lib/
INCLUDES = -I /home/fuguru/git/tinyxml2/
EXECUTABLE=Demo

# options I'll pass to the compiler.
CXXFLAGS =-Wall -c ${INCLUDES}
DEBUG    =-Wall -g -c ${INCLUDES}

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTABLE)

$(EXECUTABLE).o:
	$(CC) $(CXXFLAGS) $(EXECUTABLE).cpp
	
tinyxml2.o:
	$(CC) $(CXXFLAGS) ../tinyxml2/tinyxml2.cpp

XMLSerialization.o: XMLSerialization.h
	$(CC) $(CXXFLAGS) XMLSerialization.cpp

debug: CXXFLAGS=$(DEBUG)
debug: all


.PHONY: clean
clean:
	rm -f *.o Demo
