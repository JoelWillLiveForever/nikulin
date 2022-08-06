CC=gcc
CFLAGS=-c -Wall

all: binary detail_binary

binary: main.o
	$(CC) main.o -o binary

main.o: main.c
	$(CC) $(CFLAGS) main.c

detail_binary: detail_main.o
	$(CC) detail_main.o -o detail_binary

detail_main.o: detail_main.c
	$(CC) $(CFLAGS) detail_main.c

clean:
	rm -f *.o binary detail_binary
