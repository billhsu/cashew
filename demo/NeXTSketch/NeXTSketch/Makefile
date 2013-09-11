CC=g++
CFLAGS=-c -Wall -I. -Icontrol -Idraw -lGL -lGLU -lglut
LDFLAGS=-lGL -lGLU -lglut
SOURCES=main.cpp display.cpp draw/scene.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *.o test

