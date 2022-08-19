# компилятор и флаги
CC=g++
CFLAGS=-c -Wall
DEBUG=-O0 -g3
RELEASE=-O3

# цель по умолчанию
all: precompiled_headers debug release test

precompiled_headers: stdafx.hpp
	$(CC) $(CFLAGS) stdafx.hpp -o stdafx.hpp.gch

# объектные файлы debug
main_debug.o: main.cpp
	$(CC) $(CFLAGS) $(DEBUG) -o main_debug.o main.cpp

true_pi_selector_class_debug.o: true_pi_selector_class.cpp
	$(CC) $(CFLAGS) $(DEBUG) -o true_pi_selector_class_debug.o true_pi_selector_class.cpp

pi_monte_carlo_points_generator_class_debug.o: pi_monte_carlo_points_generator_class.cpp
	$(CC) $(CFLAGS) $(DEBUG) -o pi_monte_carlo_points_generator_class_debug.o pi_monte_carlo_points_generator_class.cpp

pi_convergence_check_class_debug.o: pi_convergence_check_class.cpp
	$(CC) $(CFLAGS) $(DEBUG) -o pi_convergence_check_class_debug.o pi_convergence_check_class.cpp

# создать бинарник в Debug режиме
debug: main_debug.o pi_monte_carlo_points_generator_class_debug.o true_pi_selector_class_debug.o pi_convergence_check_class_debug.o
	$(CC) -o debug main_debug.o true_pi_selector_class_debug.o pi_monte_carlo_points_generator_class_debug.o pi_convergence_check_class_debug.o

# создать бинарник в Release режиме
release: main.o pi_monte_carlo_points_generator_class.o true_pi_selector_class.o pi_convergence_check_class.o
	$(CC) -o release  main.o true_pi_selector_class.o pi_monte_carlo_points_generator_class.o pi_convergence_check_class.o

# бинарник, вызывающий модульные тесты
test: test.o true_pi_selector_class_test.o true_pi_selector_class.o pi_monte_carlo_points_generator_class.o 
	$(CC) -o test test.o true_pi_selector_class_test.o true_pi_selector_class.o pi_monte_carlo_points_generator_class.o

# объектные файлы release
main.o: main.cpp
	$(CC) $(CFLAGS) $(RELEASE) main.cpp

true_pi_selector_class.o: true_pi_selector_class.cpp
	$(CC) $(CFLAGS) $(RELEASE) true_pi_selector_class.cpp

pi_monte_carlo_points_generator_class.o: pi_monte_carlo_points_generator_class.cpp
	$(CC) $(CFLAGS) $(RELEASE) pi_monte_carlo_points_generator_class.cpp

pi_convergence_check_class.o: pi_convergence_check_class.cpp
	$(CC) $(CFLAGS) $(RELEASE) pi_convergence_check_class.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

true_pi_selector_class_test.o: true_pi_selector_class_test.cpp
	$(CC) $(CFLAGS) true_pi_selector_class_test.cpp

# удалить всё компилируемое
clean:
	rm -f *.o *.gch debug release test
