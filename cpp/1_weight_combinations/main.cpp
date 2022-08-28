/* Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм? */ 

#include "pch.hpp"
#include "weight_combinator_class.hpp"

int main()
{
    // целевой вес, комбинации для которого необходимо найти
    int target;
    std::cout << "Please, enter target weight for compute combinations: ";
    std::cin >> target; 

    // создаём объект класса WeightsCombinator
    WeightCombinator combinator;

    WeightCombinator::Weights weights = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};
    WeightCombinator::Combinations combinations;

    combinator.combine(target, combinations, weights);

    // выводим результат
    std::cout << "Amount combinations: " << combinations.size() << '\n';
    for (auto combination: combinations)
    {
        for (auto el: combination)
            std::cout << el << ' ';
        std::cout << '\n';
    }

    return EXIT_SUCCESS;
}
