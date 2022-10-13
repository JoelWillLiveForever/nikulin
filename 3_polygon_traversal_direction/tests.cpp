#include "pch.hpp"

#include "cross_product_class_test.hpp"
#include "direction_finder_class_test.hpp"

int main()
{
    // Test CrossProduct methods
    CrossProductTest::test();
    
    // Test DirectionFinder methods
    DirectionFinderTest::test();

    std::cout << std::endl;
    return 0;
}
