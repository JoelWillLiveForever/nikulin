# компилятор и флаги
CC=g++
CFLAGS=-c -Wall
PIC_CFLAG=-fPIC

# по умолчанию создать два бинарника
all: binary_static_lib binary_dynamic_lib

# бинарник со статической библиотекой
binary_static_lib: main.o libweicom.a
	$(CC) main.o -o binary_static_lib -L. -lweicom -lm -lstdc++

# бинарник с динамической библиотекой
binary_dynamic_lib: main.o libweicom.so
	$(CC) main.o -o binary_dynamic_lib -L. -lweicom -lm -lstdc++ -Wl,-rpath,.

# объектные файлы
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

# создать обычный объектный файл и объектный с PIC (позиционно-независимым кодом)
weights_combinator.o: weights_combinator.cpp
	$(CC) $(CFLAGS) weights_combinator.cpp
	$(CC) $(CFLAGS) $(PIC_CFLAG) weights_combinator.cpp -o weights_combinator_PIC.o

# создаём статическую библиотеку
libweicom.a: weights_combinator.o
	ar cr libweicom.a weights_combinator.o

# создаём динамическую библиотеку
libweicom.so: weights_combinator_PIC.o
	gcc -shared -o libweicom.so weights_combinator_PIC.o

# удалить всё компилируемое
clean:
	rm -f *.o *.a *.so binary_static_lib binary_dynamic_lib
