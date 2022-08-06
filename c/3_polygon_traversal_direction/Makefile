# компилятор и флаги
CC=gcc
CFLAGS=-c -Wall
PIC_CFLAG=-fPIC

# по умолчанию создать два бинарника
all: binary_static_lib binary_dynamic_lib

# бинарник со статической библиотекой
binary_static_lib: main.o libliberty_static.a
	$(CC) main.o -o binary_static_lib -L. -lliberty_static

# бинарник с динамической библиотекой
binary_dynamic_lib: main.o libliberty_dynamic.so
	$(CC) main.o -o binary_dynamic_lib -L. -lliberty_dynamic -Wl,-rpath,.

# объектные файлы
main.o: main.c
	$(CC) $(CFLAGS) main.c

# создать обычный объектный файл и объектный с PIC (позиционно-независимым кодом)
cross_product.o: cross_product.c
	$(CC) $(CFLAGS) cross_product.c
	$(CC) $(CFLAGS) $(PIC_CFLAG) cross_product.c -o cross_product_PIC.o

# создать обычный объектный файл и объектный с PIC (позиционно-независимым кодом)
polygon_traversal_direction.o: polygon_traversal_direction.c
	$(CC) $(CFLAGS) polygon_traversal_direction.c
	$(CC) $(CFLAGS) $(PIC_CFLAG) polygon_traversal_direction.c -o polygon_traversal_direction_PIC.o

# создаём статическую библиотеку
libliberty_static.a: cross_product.o polygon_traversal_direction.o
	ar cr libliberty_static.a cross_product.o polygon_traversal_direction.o

# создаём динамическую библиотеку
libliberty_dynamic.so: cross_product_PIC.o polygon_traversal_direction_PIC.o
	gcc cross_product_PIC.o polygon_traversal_direction_PIC.o -shared -o libliberty_dynamic.so

# удалить всё компилируемое
clean:
	rm -f *.o *.a *.so binary_static_lib binary_dynamic_lib
