#include <iostream>

#include "../include/true_pi_selector_class_test.hpp"

int main()
{
    if (TruePISelectorTest::test())
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
