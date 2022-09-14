CC=g++
CFLAGS=-c -Wall

all: debug release test

debug: point_class.o cross_product_class.o direction_finder_class.o main.o
	$(CC) -o debug -g3 point_class.o cross_product_class.o direction_finder_class.o main.o

release: point_class.o cross_product_class.o direction_finder_class.o main.o
	$(CC) -o release -O3 point_class.o cross_product_class.o direction_finder_class.o main.o

test: point_class.o cross_product_class.o direction_finder_class.o test.o cross_product_class_test.o direction_finder_class_test.o
	$(CC) -o test point_class.o cross_product_class.o direction_finder_class.o test.o cross_product_class_test.o direction_finder_class_test.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

point_class.o: point_class.cpp
	$(CC) $(CFLAGS) point_class.cpp -o point_class.o

cross_product_class.o: cross_product_class.cpp
	$(CC) $(CFLAGS) cross_product_class.cpp -o cross_product_class.o

direction_finder_class.o: direction_finder_class.cpp
	$(CC) $(CFLAGS) direction_finder_class.cpp -o direction_finder_class.o

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp -o test.o

cross_product_class_test.o: cross_product_class_test.cpp
	$(CC) $(CFLAGS) cross_product_class_test.cpp -o cross_product_class_test.o

direction_finder_class_test.o: direction_finder_class_test.cpp
	$(CC) $(CFLAGS) direction_finder_class_test.cpp -o direction_finder_class_test.o

clean:
	rm -f *.o debug release test
