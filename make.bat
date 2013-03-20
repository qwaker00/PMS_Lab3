gcc -c main.c -o main.o -g
gcc -c server.c -o server.o -g
gcc server.o main.o -lwsock32 -o server.exe
