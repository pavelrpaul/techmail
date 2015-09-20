# MAKEFILE

TARGET = project

SOURCES = main.cpp

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET)

$(OBJECTS): $(SOURCES)
	g++ -c $(SOURCES)

clean:
	rm -f *.o $(TARGET)
