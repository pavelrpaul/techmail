# MAKEFILE

TARGET = project

SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	gcc $(OBJECTS) -o $(TARGET)

$(OBJECTS): $(SOURCES)
	gcc -c -std=c99 $(SOURCES)

clean:
	rm -f *.o $(TARGET)
