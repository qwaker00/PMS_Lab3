all:
	$(CROSS_COMPILE)gcc main.c -o hw.o

debug:
	$(CROSS_COMPILE)gcc -g main.c -o hw.o

clean:
	rm -f *.o
