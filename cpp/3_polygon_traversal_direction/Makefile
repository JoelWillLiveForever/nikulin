CC=g++
CFLAGS=-c -Wall

all: debug release

debug: point.o cross_product.o direction_finder.o main.o
	$(CC) -o debug -g3 point.o cross_product.o direction_finder.o main.o

release: point.o cross_product.o direction_finder.o main.o
	$(CC) -o release -O3 point.o cross_product.o direction_finder.o main.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

point.o: point.cpp
	$(CC) $(CFLAGS) point.cpp -o point.o

cross_product.o: cross_product.cpp
	$(CC) $(CFLAGS) cross_product.cpp -o cross_product.o

direction_finder.o: direction_finder.cpp
	$(CC) $(CFLAGS) direction_finder.cpp -o direction_finder.o

clean:
	rm -f *.o debug release
