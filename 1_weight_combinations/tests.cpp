#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "weight_combinator_class.hpp"

/* 
тест на правильность работы класса
должен выдавать две комбинации: {100, 200} и {300}
при номенклатуре весов {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000}
и целевом весе target = 300
*/
TEST(WeightCombinatorClass, combine_basic_test)
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

    ASSERT_THAT(result, expected);
}

/* 
тест метода combinator.combine(target, result, weights)
должен выдать ошибку при отрицательном значении target
*/
TEST(WeightCombinatorClass, combine_negative_target_test)
{
    bool result = false;
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
        result = true;
    }

    ASSERT_TRUE(result);
}

/* 
тест метода combinator.combine(target, result, weights)
при пустой номенклатуре весов
должна быть выдана ошибка плохого аргумента
*/
TEST(WeightCombinatorClass, combine_empty_collection_test)
{
    bool result = true;
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
        result = false;
    }

    ASSERT_FALSE(result);
}

/* 
тест метода combinator.combine(target, result, weights)
если номенклатура больше, чем количество бит в переменной combinator (> 32)
(биты отвечают за кол-во возможных вариантов наборов гирь)
должна быть выдана ошибка плохого аргумента
*/
TEST(WeightCombinatorClass, combine_big_collection_test)
{
    bool result = false;
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
        result = true;
    }

    ASSERT_TRUE(result);
}

/* 
тест поведения при одном элементе в номенклатуре весов 
ожидается возврат одной комбинации при совпадении target и weights[0]
*/
TEST(WeightCombinatorClass, combine_one_element_in_collection_test)
{    
    WeightCombinator::Weights weights = {100};
    WeightCombinator::Combinations result;
    int target = 100;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    ASSERT_THAT(result, WeightCombinator::Combinations{ {100} });
}

/* 
тест противоположный предыдущему 
ожидается возврат 0 при различных target и weights[0]
*/
TEST(WeightCombinatorClass, combine_one_element_in_collection_bad_target_value_test)
{    
    WeightCombinator::Weights weights = {100};
    WeightCombinator::Combinations result;
    int target = 200;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    ASSERT_THAT(result, WeightCombinator::Combinations());
}

/* 
ожидается возврат 0 при различных target = 2637 при несоответствующей номенклатуре весов
*/
TEST(WeightCombinatorClass, combine_zero_combination_in_result_test)
{
    WeightCombinator::Combinations expected;    // empty
    
    WeightCombinator::Weights weights = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};
    WeightCombinator::Combinations result;
    int target = 2637;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    ASSERT_THAT(result, expected);
}

/* 
ожидается возврат 1, максимальный вес "поддерживаемый" номенклатурой == сумме всех весов из номенклатуры
это одна комбинация всегда
*/
TEST(WeightCombinatorClass, combine_max_combination_in_result_test)
{
    WeightCombinator::Combinations expected = {
        {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000}
    };
    
    WeightCombinator::Weights weights = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};
    WeightCombinator::Combinations result;
    int target = 11200;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    ASSERT_THAT(result, expected);
}

/* 
программа должна работать, даже если номенклатура имеет одинаковые веса
при номенклатуре {100, 100, 100, 100, 100, 100, 100}, т.е. 7 гирь
заданный вес target = 700 -> сумма всех семи гирь из номенклатуры даёт комбинацию
*/
TEST(WeightCombinatorClass, combine_all_weights_are_same_one_combination_in_result_test)
{
    WeightCombinator::Combinations expected = {
        {100, 100, 100, 100, 100, 100, 100}
    };
    
    WeightCombinator::Weights weights = {100, 100, 100, 100, 100, 100, 100};
    WeightCombinator::Combinations result;
    int target = 700;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    ASSERT_THAT(result, expected);
}

/* 
усложнение предыдущего теста
вместо одной одинаковый гири -> две одинаковые
*/
TEST(WeightCombinatorClass, combine_all_weights_are_same_two_combination_in_result_test)
{
    WeightCombinator::Combinations expected = {
        {100, 100, 100},
        {100, 200}
    };
    
    WeightCombinator::Weights weights = {100, 100, 200, 200, 200, 100};
    WeightCombinator::Combinations result;
    int target = 300;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    ASSERT_THAT(result, expected);
}

// TODO
// FIXME
// TEST NOT WORK
/* 
усложнение предыдущего теста
вместо одной одинаковый гири -> несколько одинаковых
*/
// TEST(WeightCombinatorClass, combine_all_weights_are_same_some_combination_in_result_test)
// {
//     WeightCombinator::Combinations expected = {
//         {100, 100, 100, 100, 100},
//         {100, 100, 100, 200},
//         {100, 200, 200},
//         // {100, 100, 100, 200},
//         // {100, 200, 200},
//         {250, 250},
//         {100, 400},
//         {500}
//     };
    
//     WeightCombinator::Weights weights = {100, 100, 100, 100, 100, 200, 200, 200, 250, 250, 400, 400, 500};
//     WeightCombinator::Combinations result;
//     int target = 500;

//     WeightCombinator combinator;
//     combinator.combine(target, result, weights);

//     ASSERT_THAT(result, expected);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

	return RUN_ALL_TESTS();
}