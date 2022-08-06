# компилятор
CC=gcc

# флаги компилятора
CFLAGS=-c -Wall
LDFLAGS=-lOpenCL

# цель по умолчанию
all: binary

# линкуем объектные файлы в бинарник
binary: main.o
	$(CC) main.o -o binary $(LDFLAGS)

# объектный файл main.o
main.o: main.c
	$(CC) $(CFLAGS) main.c

# удалить объектные файлы и бинарник
clean:
	rm -f *.o binary
