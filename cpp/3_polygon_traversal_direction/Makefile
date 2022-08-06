CC=gcc
CFLAGS=-c -Wall

all: debug release

debug: main.o polygon_traversal_direction.o
	$(CC) -o debug -g3 main.o polygon_traversal_direction.o

release: main.o polygon_traversal_direction.o
	$(CC) -o release -O3 main.o polygon_traversal_direction.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

polygon_traversal_direction.o: polygon_traversal_direction.cpp
	$(CC) $(CFLAGS) polygon_traversal_direction.cpp -o polygon_traversal_direction.o

clean:
	rm -f *.o debug release
