#include <gtest/gtest.h>
#include <gmock/gmock.h>

// протестим CPP проги
#include "pi_monte_carlo_points_generator_class.hpp"
#include "pi_convergence_check_class.hpp"
#include "true_pi_selector_class.hpp"
#include "samples.hpp"

// протестим C проги
extern "C"
{
    #include "counters.h"
}

TEST(TruePISelectorClass, basic_usage_test)
{
    TruePISelector selector(6, 1000, 2, 0.01);

    double pi = 0;
    pi = selector.select_pi();

    ASSERT_NEAR(pi, 3.14, 0.01);
}

TEST(TruePISelectorClass, zero_total_pi_test)
{
    try
    {
        TruePISelector selector(0, 1000, 2, 0.01);

        double pi = 0;
        pi = selector.select_pi();

        FAIL() << "Expected zero total_pi exception";
    }
    catch (std::exception const& e)
    {
        EXPECT_EQ(e.what(), std::string("Zero total_pi"));
    }
    catch (...)
    {
        FAIL() << "Expected zero total_pi exception";
    }
}

TEST(TruePISelectorClass, big_points_start_test)
{
    try
    {
        TruePISelector selector(6, UINT_MAX + 1, 2, 0.01);

        double pi = 0;
        pi = selector.select_pi();

        FAIL() << "Expected zero total_pi exception";
    }
    catch (std::overflow_error const& e)
    {
        SUCCEED() << e.what();
    }
    catch (...)
    {
        FAIL() << "Expected zero total_pi exception";
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}