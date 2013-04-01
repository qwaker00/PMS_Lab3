
CC=$(CROSS_COMPILE)gcc 
CFLAGS=-c -Wall -x c
LDFLAGS=-pthread

SOURCES=main.c wserver.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=server

all: $(SOURCES) $(TARGET) 

process: CC+=-D_MULTIPROCESS
process: all

process_debug: CC+=-D_MULTIPROCESS -D_DEBUG
process_debug: debug
 
debug: CC+=-D_DEBUG -g
debug: all

release: CC+=-O3
release: all

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	sudo ./$(TARGET)

clean:
	rm -f *.o $(TARGET)
