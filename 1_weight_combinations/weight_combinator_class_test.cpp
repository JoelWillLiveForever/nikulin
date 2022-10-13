#include "weight_combinator_class_test.hpp"
#include "weight_combinator_class.hpp"

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