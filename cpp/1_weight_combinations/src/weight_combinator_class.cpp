#include "../include/weight_combinator_class.hpp"

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

// Tests:
bool WeightCombinatorTest::combine_basic_test()
{
    WeightCombinator::Combinations expected = {
        {100, 200},
        {300}
    };
    
    WeightCombinator::Weights weights = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};
    WeightCombinator::Combinations result;
    int target = 300;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    return result == expected;
}

bool WeightCombinatorTest::combine_negative_target_test()
{
    try
    {
        WeightCombinator::Weights weights = {100, 200, 300};
        WeightCombinator::Combinations result;
        int target = -600;

        WeightCombinator combinator;
        combinator.combine(target, result, weights);
    }
    catch ( std::invalid_argument const & )         // expected
    {
        return true;
    }

    return false;
}

bool WeightCombinatorTest::combine_empty_collection_test()
{
    try
    {
        WeightCombinator::Weights weights;          // empty
        WeightCombinator::Combinations result;
        int target = 123;

        WeightCombinator combinator;
        combinator.combine(target, result, weights);
    }
    catch ( std::invalid_argument const & )         // expected
    {
        return true;
    }

    return false;
}

bool WeightCombinatorTest::combine_big_collection_test()
{
    try
    {
        WeightCombinator::Weights weights;
        WeightCombinator::Combinations result;
        int target = 123;

        for (int i = 0; i < WeightCombinator::get_allowed_bits() * 10; i++)
            weights.push_back(i);

        WeightCombinator combinator;
        combinator.combine(target, result, weights);
    }
    catch ( std::invalid_argument const & ) // expected
    {
        return true;
    }

    return false;
}

bool WeightCombinatorTest::combine_one_element_in_collection_test()
{
    WeightCombinator::Combinations expected = {
        {100}
    };
    
    WeightCombinator::Weights weights = {100};
    WeightCombinator::Combinations result;
    int target = 100;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    return result == expected;
}

bool WeightCombinatorTest::combine_zero_combination_in_result_test()
{
    WeightCombinator::Combinations expected;    // empty
    
    WeightCombinator::Weights weights = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};
    WeightCombinator::Combinations result;
    int target = 2637;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    return result == expected;
}

bool WeightCombinatorTest::combine_max_combination_in_result_test()
{
    WeightCombinator::Combinations expected = {
        {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000}
    };
    
    WeightCombinator::Weights weights = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};
    WeightCombinator::Combinations result;
    int target = 11200;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    return result == expected;

}

bool WeightCombinatorTest::combine_all_weights_are_same_one_combination_in_result_test()
{
    WeightCombinator::Combinations expected = {
        {100, 100, 100, 100, 100, 100, 100}
    };
    
    WeightCombinator::Weights weights = {100, 100, 100, 100, 100, 100, 100};
    WeightCombinator::Combinations result;
    int target = 700;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    return result == expected;
}

bool WeightCombinatorTest::combine_all_weights_are_same_two_combination_in_result_test()
{
    WeightCombinator::Combinations expected = {
        {100, 100, 100},
        {100, 200}
    };
    
    WeightCombinator::Weights weights = {100, 100, 100, 200, 200, 200};
    WeightCombinator::Combinations result;
    int target = 300;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    return result == expected;
}

int WeightCombinatorTest::test()
{
    if ( !combine_basic_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_basic_test()\"\n";
        return EXIT_FAILURE;
    }
    
    if ( !combine_negative_target_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_negative_target_test()\"\n";
        return EXIT_FAILURE;
    }

    if ( !combine_empty_collection_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_empty_collection_test()\"\n";
        return EXIT_FAILURE;
    }
    
    if ( !combine_big_collection_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_big_collection_test()\"\n";
        return EXIT_FAILURE;
    }

    if ( !combine_one_element_in_collection_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_one_element_in_collection_test()\"\n";
        return EXIT_FAILURE;
    }

    if ( !combine_zero_combination_in_result_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_zero_combination_in_result_test()\"\n";
        return EXIT_FAILURE;
    }

    if ( !combine_max_combination_in_result_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_max_combination_in_result_test()\"\n";
        return EXIT_FAILURE;
    }

    if ( !combine_all_weights_are_same_one_combination_in_result_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_all_weights_are_same_one_combination_in_result_test()\"\n";
        return EXIT_FAILURE;
    }

    if ( !combine_all_weights_are_same_two_combination_in_result_test() )
    {
        std::cout << "\n\tFAIL --- \"WeightCombinatorTest::combine_all_weights_are_same_two_combination_in_result_test()\"\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
