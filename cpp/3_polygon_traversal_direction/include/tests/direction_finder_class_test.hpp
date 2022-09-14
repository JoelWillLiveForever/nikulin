#pragma once

#include "../pch.hpp"
#include "../direction_finder_class.hpp"

class DirectionFinderTest
{
private:
    static bool find_direction_test_non_convex_polygon_anti_clockwise_points();
    static bool find_direction_test_non_convex_polygon_clockwise_points();
    static bool find_direction_test_convex_polygon_anti_clockwise_points();
    static bool find_direction_test_convex_polygon_clockwise_points();

public:
    static void test(); // тестируем весь класс

};
