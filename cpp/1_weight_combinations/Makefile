# компилятор и флаги
CC=g++
CFLAGS=-c -Wall
PIC_CFLAG=-fPIC

# по умолчанию создать два бинарника
all: binary_static_lib binary_dynamic_lib test

# бинарник со статической библиотекой
binary_static_lib: main.o libweicom.a
	$(CC) main.o -o binary_static_lib -L. -lweicom -lm -lstdc++

# бинарник с динамической библиотекой
binary_dynamic_lib: main.o libweicom.so
	$(CC) main.o -o binary_dynamic_lib -L. -lweicom -lm -lstdc++ -Wl,-rpath,.

test: test.o weights_combinator_class_test.o weights_combinator_class.o
	$(CC) -o test test.o weights_combinator_class_test.o weights_combinator_class.o

# объектные файлы
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

# создать обычный объектный файл и объектный с PIC (позиционно-независимым кодом)
weights_combinator_class.o: weights_combinator_class.cpp
	$(CC) $(CFLAGS) weights_combinator_class.cpp
	$(CC) $(CFLAGS) $(PIC_CFLAG) weights_combinator_class.cpp -o weights_combinator_class_PIC.o

# создаём статическую библиотеку
libweicom.a: weights_combinator_class.o
	ar cr libweicom.a weights_combinator_class.o

# создаём динамическую библиотеку
libweicom.so: weights_combinator_class_PIC.o
	gcc -shared -o libweicom.so weights_combinator_class_PIC.o

weights_combinator_class_test.o: weights_combinator_class_test.cpp
	$(CC) $(CFLAGS) weights_combinator_class_test.cpp

# удалить всё компилируемое
clean:
	rm -f *.o *.a *.so *.out binary_static_lib binary_dynamic_lib test
