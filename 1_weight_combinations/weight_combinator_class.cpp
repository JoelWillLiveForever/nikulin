#include "weight_combinator_class.hpp"

void WeightCombinator::combine(int target, WeightCombinator::Combinations &combinations, WeightCombinator::Weights &weights)
{
    // если номенклатуры весов не заданы (пустой вектор), то кол-во вариантов точно == 0
    // или их кол-во больше числа битов в combinator (32)
    if ( weights.size() == 0 || weights.size() > static_cast<size_t>(allowed_bits_) )
        throw std::invalid_argument( "Error! The nomenclature list is empty or his size more than " + std::to_string(allowed_bits_) + "!" );

    // проверка на отрицательный target
    if ( target < 0 )
        throw std::invalid_argument( "Error! Negative target weight!" );

    // число для проверки комбинаций гирь, с помощью битов числа
    unsigned int combinator = 1;
    
    // сортировка набора гирь, вдруг веса идут не по порядку
    std::sort(weights.begin(), weights.end());

    // максиммальное число комбинаций и итератор на номенклатуру весов
    unsigned int all_combinations = pow(2, weights.size());
    WeightCombinator::Weights::iterator iter = weights.begin();

    // проходимся по всем уникальным комбинациям, увеличивая combinator на 1
    while (combinator < all_combinations)
    {
        int bit = 0; // номер проверяемого бита + по совместительству индекс гири
        int combinator_copy = combinator;
        int local_target = 0;

        std::vector<int> curr_combination;
        while (combinator_copy != 0)
        {
            if (combinator_copy & 1)
            {
                // получить размер гири из массива гирь, если бит равен 1
                int weight = *(iter + bit);
                
                local_target += weight;
                curr_combination.push_back(weight);
            }

            combinator_copy >>= 1; // сместить отсавшиеся биты вправо
            bit++;
        }
        
        // если текущая комбинация дала необходимый вес, то сохранить комбинацию
        if (local_target == target)
            combinations.push_back(curr_combination);

        combinator++;
    }
    
    combinations.erase(unique(combinations.begin(), combinations.end()), combinations.end());   // удалить дубликаты
}