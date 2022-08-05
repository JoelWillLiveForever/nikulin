/* Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм? */ 

#include <iostream>
#include <iterator>
#include "weight_combinations.hpp"

int main()
{
    // инициализация статического массива с размерами гирь
    int weights[] = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};

    // получить указатели на адрес первого элемента и на адрес элемента следующего за последним элементом массива
    int *begin = weights;
    int *end = weights + sizeof(weights) / sizeof(*weights);

    // целевой вес, комбинации для которого необходимо найти
    int target;
    std::cout << "Please, enter target weight for compute combinations: ";
    std::cin >> target; 

    // вызов функции из файла weight_combinations.cpp
    int combinations_count = get_weight_combinations(begin, end, target);
    std::cout << "Combinations: " << combinations_count << std::endl;

    return 0;
}
