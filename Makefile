CC=g++
CFLAGS=-c -Wall -framework OpenGL -framework GLUT
LDFLAGS=-framework OpenGL -framework GLUT
SOURCES=pacman.cc Cell.cc Map.cc Graph.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=pacman.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@