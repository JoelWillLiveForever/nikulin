#pragma once

#include "pch.hpp"

class WeightCombinator
{
public:
    typedef std::vector<int> Weights;                           // тип для хранения номенклатуры гирь
    typedef std::vector<std::vector<int>> Combinations;         // тип для хранения комбинаций

private:
    const char allowed_bits = sizeof(unsigned int) * 8;         // максимальное количество гирь, которое можно задать    

public:

    void combine(int target, 
            WeightCombinator::Combinations &combinations, 
            WeightCombinator::Weights &weights);                // метод поиска комбинаций для заданного веса

};

class WeightCombinatorTest
{
private:
    static bool combine_basic_test(); 
    static bool combine_empty_collection_test();
    static bool combine_one_element_in_collection_test();
    static bool combine_zero_combination_in_result_test();
    static bool combine_all_weights_are_same_one_combination_in_result_test();
    static bool combine_all_weights_are_same_two_combination_in_result_test();

public:
    static int test();

};
