CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -g
all: main

.PHONY: clean

structs.o: structs.cpp structs.h
	$(CC) $(CFLAGS) -c structs.cpp -o structs.o
input.o: input.cpp input.h
	$(CC) $(CFLAGS) -c input.cpp -o input.o
main.o: main.cpp structs.h input.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o
main: structs.o input.o main.o
	$(CC) $(CFLAGS) structs.o input.o main.o -o nokiacomposer

clean:
	rm -f *.o