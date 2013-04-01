
CC=$(CROSS_COMPILE)gcc 
CFLAGS=-c -Wall -x c
LDFLAGS=

SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=get

all: $(SOURCES) $(TARGET) 

debug: CC+=-D_DEBUG -g
debug: all

release: CC+=-O3
release: all

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	sudo ./$(TARGET) localhost 80 /index.htm

clean:
	rm -f *.o $(TARGET)
