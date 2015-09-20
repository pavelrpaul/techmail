# MAKEFILE

TARGET = project

SOURCES = main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET)

$(OBJECTS): $(SOURCES)
	g++ -c $(SOURCES)

clean:
	rm -f *.o $(TARGET)
