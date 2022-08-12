# компилятор и флаги
CC=g++
CFLAGS=-c -Wall

# цель по умолчанию
all: precompiled_headers debug release test

precompiled_headers: stdafx.hpp stdafx.cpp
	$(CC) $(CFLAGS) stdafx.hpp -o stdafx.hpp.gch

# создать бинарник в Debug режиме
debug: main.o pi_monte_carlo_points_generator_class.o true_pi_selector_class.o
	$(CC) -g3 -o debug main.o true_pi_selector_class.o pi_monte_carlo_points_generator_class.o

# создать бинарник в Release режиме
release: main.o pi_monte_carlo_points_generator_class.o true_pi_selector_class.o
	$(CC) -O3 -o release  main.o true_pi_selector_class.o pi_monte_carlo_points_generator_class.o

# бинарник, вызывающий модульные тесты
test: test.o true_pi_selector_class_test.o true_pi_selector_class.o pi_monte_carlo_points_generator_class.o 
	$(CC) -o test test.o true_pi_selector_class_test.o true_pi_selector_class.o pi_monte_carlo_points_generator_class.o

# объектные файлы
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

true_pi_selector_class.o: true_pi_selector_class.cpp
	$(CC) $(CFLAGS) true_pi_selector_class.cpp

pi_monte_carlo_points_generator_class.o: pi_monte_carlo_points_generator_class.cpp
	$(CC) $(CFLAGS) pi_monte_carlo_points_generator_class.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

true_pi_selector_class_test.o: true_pi_selector_class_test.cpp
	$(CC) $(CFLAGS) true_pi_selector_class_test.cpp

# удалить всё компилируемое
clean:
	rm -f *.o *.gch debug release test
