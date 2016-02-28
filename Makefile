# the compiler to use.
CC=g++
RM=\rm *.o Demo
src =$(wildcard *.cpp)
OBJS =$(src:.cpp=.o)

LIBB = /usr/lib /home/fuguru/git/tinyxml2/lib ./lib
LIBINCLUDE = /home/fuguru/git/tinyxml2

LDFLAGS = $(addprefix -L,$(LIBB))
LIBS =-lxmls -ltinyxml2 

EXECUTABLE=Demo

# options I'll pass to the compiler.
CXXFLAGS =-std=c++11 -m64 -static -Wall -c $(addprefix -I,$(LIBINCLUDE))
DEBUG    =-std=c++11 -m64 -static -Wall -g -c $(addprefix -I,$(LIBINCLUDE))

all: lib $(EXECUTABLE)

$(EXECUTABLE): $(EXECUTABLE).o
	$(CC) $^ $(LDFLAGS) -o $@ $(LIBS)

$(EXECUTABLE).o: $(EXECUTABLE).cpp
	$(CC) $(CXXFLAGS) $^
	
XMLSerialization.o: XMLSerialization.cpp XMLSerialization.h
	$(CC) $(CXXFLAGS) XMLSerialization.cpp

debug: CXXFLAGS=$(DEBUG)
debug: all

lib: XMLSerialization.o
	ar rvs lib/libxmls.a XMLSerialization.o
	rm -f XMLSerialization.o

.PHONY: clean
clean:
	rm -f *.o *~ Demo ./lib/*.a
