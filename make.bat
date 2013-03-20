gcc -c main.c -o main.o
gcc -c server.c -o server.o
gcc main.o server.o -lwsock32 -o server.exe
