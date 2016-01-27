CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -g
all: main

.PHONY: clean

structs.o: structs.cpp structs.h
	$(CC) $(CFLAGS) -c structs.cpp -o structs.o
main.o: main.cpp structs.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o
main: structs.o main.o
	$(CC) $(CFLAGS) structs.o main.o -o melobeep

clean:
	rm -f *.o