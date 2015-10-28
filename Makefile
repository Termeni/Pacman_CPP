CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=pacman.cc Cell.cc Map.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=pacman

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@