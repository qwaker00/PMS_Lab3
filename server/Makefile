
CC=$(CROSS_COMPILE)gcc 
CFLAGS=-c -Wall
LDFLAGS=

SOURCES=main.c server.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=server

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	sudo ./$(TARGET)

clean:
	rm -f *.o $(TARGET)
