/* Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм? */

#include "weight_combinations.hpp"
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

int get_weight_combinations(int *begin, int *end, int target)
{   
    const int weights_size = end - begin; // кол-во гирь
    const int allowed_bits = sizeof(unsigned int) * 8; // доступное кол-во бит в беззнаковом int

    // вернуть -1 (код ошибки), если кол-во гирь больше чем количество бит в combinator
    if (weights_size > allowed_bits) return -1;

    // число для проверки комбинаций гирь, с помощью битов числа
    unsigned int combinator = 1;
    
    // сортировка массива с гирями, вдруг веса идут не по порядку
    std::sort(begin, end);
    
    // счётчик подходящих комбинаций
    int result = 0;

    // проходимся по всем уникальным комбинациям, увеличивая combinator на 1
    while (combinator < pow(2, weights_size))
    {
        int bit = 0; // номер проверяемого бита + по совместительству индекс массива гирь
        int combinator_copy = combinator;
        int local_target = 0;

        while (combinator_copy != 0)
        {
            if (combinator_copy & 1)
                local_target += *(begin + bit); // получить размер гири из массива гирь, если бит равен 1

            combinator_copy >>= 1; // сместить отсавшиеся биты вправо
            bit++;
        }

        if (local_target == target) // если текущая комбинация дала необходимый вес, то увеличить счётчик на 1
            result++;

        combinator++;
    }

    return result;
}
