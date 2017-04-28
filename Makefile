CC  = g++
CXX = g++

INCLUDES = -I../include

CFLAGS   = -Wall -O2 -std=c++1z -fconcepts $(INCLUDES)
CXXFLAGS = -Wall -O2 -std=c++1z -fconcepts $(INCLUDES)

LDFLAGS = 
LDLIBS  = -lpthread

all: doc test

.PHONY: doc
doc:
	doxygen

.PHONY: test
test:
	$(MAKE) -C test/

.PHONY: clean
clean:
	rm -rf doc/
	rm -f *.o

.PHONY: all
all: clean default
