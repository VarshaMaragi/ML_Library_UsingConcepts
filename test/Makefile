CC  = g++
CXX = g++

INCLUDES = -I../include

CFLAGS   = -g -Wall -O2 -std=c++1z -fconcepts $(INCLUDES)
CXXFLAGS = -g -Wall -O2 -std=c++1z -fconcepts $(INCLUDES)

LDFLAGS = -g
LDLIBS  = -lpthread

.PHONY: default
default: Projectmain

Projectmain: Projectmain.o

Projectmain.o: Projectmain.cpp

.PHONY: clean
clean:
	rm -f *~ *.o libml-test a.out core

.PHONY: all
all: clean default
