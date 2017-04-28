CC  = g++
CXX = g++

INCLUDES = -I../include

CFLAGS   = -Wall -O2 -std=c++1z -fconcepts $(INCLUDES)
CXXFLAGS = -Wall -O2 -std=c++1z -fconcepts $(INCLUDES)

LDFLAGS = 
LDLIBS  = -lpthread

.PHONY: default
default: Projectmain

Projectmain: Projectmain.o

Projectmain.o: Projectmain.cpp

.PHONY: clean
clean:
	rm -f *~ *.o libml-test a.out core Projectmain

.PHONY: all
all: clean default
