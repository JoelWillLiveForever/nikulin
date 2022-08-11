#include "weights_combinator_class.hpp"

#include <algorithm>
#include <cmath>

// конструктор класса
WeightsCombinator::WeightsCombinator(int* weights, size_t weights_size):
    my_weights(weights), my_weights_size(weights_size)
{ } 

// set-метод для массива гирь
void WeightsCombinator::set_weights(int* weights, size_t weights_size)
{
    my_weights = weights;
    my_weights_size = weights_size;
}  
    
// get-метод для массива гирь
int* WeightsCombinator::get_weights()
{
    return my_weights;
}

// get-метод для размера массива гирь
size_t WeightsCombinator::get_weights_size()
{
    return my_weights_size;
}

// метод поиска комбинаций для заданного веса
int WeightsCombinator::combine(int target)
{
    // вернуть -1 (код ошибки), если кол-во гирь больше чем количество бит в combinator
    if (my_weights_size > static_cast<size_t>(allowed_bits)) return -1;

    // число для проверки комбинаций гирь, с помощью битов числа
    unsigned int combinator = 1;
    
    // сортировка массива с гирями, вдруг веса идут не по порядку
    std::sort(my_weights, my_weights + my_weights_size);

    // счётчик подходящих комбинаций
    int result = 0;

    // проходимся по всем уникальным комбинациям, увеличивая combinator на 1
    while (combinator < pow(2, my_weights_size))
    {
        int bit = 0; // номер проверяемого бита + по совместительству индекс массива гирь
        int combinator_copy = combinator;
        int local_target = 0;

        while (combinator_copy != 0)
        {
            if (combinator_copy & 1)
                local_target += *(my_weights + bit); // получить размер гири из массива гирь, если бит равен 1

            combinator_copy >>= 1; // сместить отсавшиеся биты вправо
            bit++;
        }

        if (local_target == target) // если текущая комбинация дала необходимый вес, то увеличить счётчик на 1
            result++;

        combinator++;
    }

    return result;
}
