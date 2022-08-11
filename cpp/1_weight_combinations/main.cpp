/* Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм? */ 

#include <iostream>
#include <iterator>

#include "weights_combinator_class.hpp"

int main()
{
    // инициализация статического массива с размерами гирь
    int weights[] = {200, 3000, 500, 300, 1000, 1200, 1400, 1500, 2000, 100};

    int* begin = weights;
    int* end = weights + sizeof(weights) / sizeof(weights[0]);
    int size = end - begin;

    // целевой вес, комбинации для которого необходимо найти
    int target;
    std::cout << "Please, enter target weight for compute combinations: ";
    std::cin >> target; 

    // создаём объект класса WeightsCombinator
    WeightsCombinator combinator(weights, size);

    // выводим результат
    std::cout << "Combinations: " << combinator.combine(target) << std::endl;
    return 0;
}
