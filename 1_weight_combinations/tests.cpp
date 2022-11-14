#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/process.hpp>

// протестим CPP проги
#include "weight_combinator.hpp"

// протестим C проги
extern "C"
{
    #include "wc_module.h"
};

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
должен выдать ошибку при нулевом значении target
*/
TEST(WeightCombinatorClass, combine_zero_target_test)
{
    WeightCombinator::Weights weights = { 100, 200, 300 };
    WeightCombinator::Combinations result;
    int target = 0;

    EXPECT_THROW({
        try
        {
            WeightCombinator combinator;
            combinator.combine(target, result, weights);
        }
        catch(std::exception const& e)
        {
            EXPECT_STREQ("Zero target weight", e.what());
            throw;
        }
    }, std::exception);
}

/*
сокращённый вариант предыдущего теста
*/
TEST(WeightCombinatorClass, combine_zero_target_test_2)
{

    WeightCombinator::Weights weights = {100, 200, 300};
    WeightCombinator::Combinations result;
    int target = 0;

    WeightCombinator combinator;

    EXPECT_THROW(combinator.combine(target, result, weights), std::exception);
}

/*
тест метода combinator.combine(target, result, weights)
при пустой номенклатуре весов
должна быть выдана ошибка плохого аргумента
*/
TEST(WeightCombinatorClass, combine_empty_collection_test)
{
    WeightCombinator::Weights weights;          // empty
    WeightCombinator::Combinations result;
    int target = 123;

    EXPECT_THROW({
        try
        {
            WeightCombinator combinator;
            combinator.combine(target, result, weights);
        }
        catch (std::exception const& e)
        {
            EXPECT_STREQ("Invalid weights size", e.what());
            throw;
        }
    }, std::exception);
}

/*
тест метода combinator.combine(target, result, weights)
если номенклатура больше, чем количество бит в переменной combinator (> 32)
(биты отвечают за кол-во возможных вариантов наборов гирь)
должна быть выдана ошибка плохого аргумента
*/
TEST(WeightCombinatorClass, combine_big_collection_test)
{
    WeightCombinator::Weights weights(100);
    WeightCombinator::Combinations result;
    int target = 123;

    EXPECT_THROW({
        try
        {
            WeightCombinator combinator;
            combinator.combine(target, result, weights);
        }
        catch (std::exception const& e)
        {
            EXPECT_STREQ("Invalid weights size", e.what());
            throw;
        }
    }, std::exception);
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
TEST(WeightCombinatorClass, combine_all_weights_are_same_some_combination_in_result_test)
{
    WeightCombinator::Combinations expected = {
        {100, 100, 100, 100, 100},
        {100, 100, 100, 200},
        {100, 200, 200},
        // {100, 100, 100, 200},
        // {100, 200, 200},
        {250, 250},
        {100, 400},
        {500}
    };
   
    WeightCombinator::Weights weights = {100, 100, 100, 100, 100, 200, 200, 200, 250, 250, 400, 400, 500};
    WeightCombinator::Combinations result;
    int target = 500;

    WeightCombinator combinator;
    combinator.combine(target, result, weights);

    ASSERT_THAT(result, expected);
}

namespace bp = boost::process;
TEST(Main, basic_usage_test)
{
    bp::ipstream pipe_stream;

    #ifdef _WIN32
        bp::child c("WeightCombinations-CPP.exe", bp::std_out > pipe_stream);
    #else
        bp::child c("WeightCombinations-CPP", bp::std_out > pipe_stream);
    #endif

    std::string line;
    std::ostringstream out;

    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        out << line;
    c.wait();

#ifdef _WIN32
    ASSERT_EQ(out.str(), "100 200 300 500 1000 1200 1400 1500 2000 3000 \r");
#else
    ASSERT_EQ(out.str(), "100 200 300 500 1000 1200 1400 1500 2000 3000 ");
#endif
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
