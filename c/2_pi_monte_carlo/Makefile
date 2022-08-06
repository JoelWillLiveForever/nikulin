# компилятор
CC=gcc

# флаги компилятора
CFLAGS=-c -Wall

# цель по умолчанию
all: binary

# линкуем объектные файлы в бинарник
binary: main.o xor_shift.o
	$(CC) main.o xor_shift.o -o binary

# объектный файл main.o
main.o: main.c
	$(CC) $(CFLAGS) main.c

# объектный файл xor_shift.o
xor_shift.o: xor_shift.c
	$(CC) $(CFLAGS) xor_shift.c

# удалить объектные файлы и бинарник
clean:
	rm -f *.o binary
