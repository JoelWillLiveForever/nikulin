#pragma once

#include "weight_combinator_class.hpp"

class WeightCombinatorTest
{
private:
    static bool combine_basic_test(); 

    static bool combine_negative_target_test();

    static bool combine_empty_collection_test();
    static bool combine_big_collection_test();

    static bool combine_one_element_in_collection_test();

    static bool combine_max_combination_in_result_test();
    static bool combine_zero_combination_in_result_test();

    static bool combine_all_weights_are_same_one_combination_in_result_test();
    static bool combine_all_weights_are_same_two_combination_in_result_test();

public:
    static int test();

};