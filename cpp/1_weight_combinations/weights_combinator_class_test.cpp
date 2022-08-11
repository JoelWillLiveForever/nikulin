#include "weights_combinator_class_test.hpp"

bool WeightsCombinatorTest::combine_test()
{
    int expected = 14;
    
    int weights[] = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};

    int *begin = weights;
    int *end = weights + sizeof(weights) / sizeof(weights[0]);
    int size = end - begin;

    int target = 7000;

    WeightsCombinator combinator(weights, size);
    int result = combinator.combine(target);

    return expected == result;
}

void WeightsCombinatorTest::test()
{
    std::cout << "\n\tTesting \"WeightsCombinator\" class:"

        << "\n\t\t"
        << (combine_test() ? "OK" : "FAIL")
        << " --- \"combine()\""
        << std::endl;
}
