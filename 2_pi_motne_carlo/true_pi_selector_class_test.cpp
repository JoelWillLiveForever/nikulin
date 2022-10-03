#include "true_pi_selector_class_test.hpp"

bool TruePISelectorTest::select_pi_test()
{
    double expected = 3.141;
    double eps = 0.001;

    unsigned int total_pi = 5;
    unsigned int points_start = 1000;
    unsigned int points_multiplier = 2;

    TruePISelector obj(total_pi, points_start, points_multiplier, eps);
    double result = obj.select_pi();
    
    // std::cout << "\nResult: " << result;
    // std::cout << "\nFABS: " << std::fabs(expected - result);

    return std::fabs(expected - result) <= eps;
}

int TruePISelectorTest::test()
{
    if ( !select_pi_test() )
    {
        std::cout << "\n\tFAIL --- \"TruePISelectorTest::select_pi_test()\"\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
