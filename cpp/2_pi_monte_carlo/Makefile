# компилятор и флаги
CC=g++
CFLAGS=-c -Wall

# цель по умолчанию
all: debug release

# создать бинарник в Debug режиме
debug: main.o
	$(CC) -o debug -g3 main.o

# создать бинарник в Release режиме
release: main.o
	$(CC) -o release -O3 main.o

# объектные файлы
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

# удалить всё компилируемое
clean:
	rm -f *.o debug release
