#include "../include/pch.hpp"

#include "../include/tests/cross_product_class_test.hpp"
#include "../include/tests/direction_finder_class_test.hpp"

int main()
{
    // Test CrossProduct methods
    CrossProductTest::test();
    
    // Test DirectionFinder methods
    DirectionFinderTest::test();

    std::cout << std::endl;
    return 0;
}
