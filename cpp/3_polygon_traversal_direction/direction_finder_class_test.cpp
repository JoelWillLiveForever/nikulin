#include "direction_finder_class_test.hpp"

#include <iostream>

// невыпуклый многоугольник с координатами вершин заданными против часовой стрелки
bool DirectionFinderTest::find_direction_test_non_convex_polygon_anti_clockwise_points()
{
    int expected = -1;       // ожидаемый результат
    
    // координаты вершин в векторе
    std::vector<Point> points;

    points.push_back(Point {2.0, 5.0});
    points.push_back(Point {3.5, 5.0});
    points.push_back(Point {2.5, 3.0});
    points.push_back(Point {6.0, 5.0});
    points.push_back(Point {7.5, 1.5});
    points.push_back(Point {7.5, 4.5});
    points.push_back(Point {10.5, 5.5});
    points.push_back(Point {7.5, 9.0});
    points.push_back(Point {5.5, 6.0});
    points.push_back(Point {2.0, 7.5});

    DirectionFinder df(points);
    int result = df.find_direction();

    return result == expected;
}

// невыпуклый многоугольник с координатами вершин заданными по часовой стрелке
bool DirectionFinderTest::find_direction_test_non_convex_polygon_clockwise_points()
{
    int expected = 1;       // ожидаемый результат

    // координаты вершин в векторе
    std::vector<Point> points;
 
    points.push_back(Point {5.5, 6.0});
    points.push_back(Point {7.5, 9.0});
    points.push_back(Point {10.5, 5.5});
    points.push_back(Point {7.5, 4.5});
    points.push_back(Point {6.5, 2.0});
 
    DirectionFinder df(points);
    int result = df.find_direction();

    return result == expected;
}

// выпуклый многоугольник с координатами вершин заданными против часовой стрелки
bool DirectionFinderTest::find_direction_test_convex_polygon_anti_clockwise_points()
{
    int expected = -1;

    std::vector<Point> points;

    points.push_back(Point {5.0, -2.0});
    points.push_back(Point {2.5, 3.5});
    points.push_back(Point {-4.0, 3.0});
    points.push_back(Point {-3.5, -3.5});
    points.push_back(Point {1.0, -5.0});

    DirectionFinder df(points);
    int result = df.find_direction();

    return result == expected;
}

// выпуклый многоугольник с координатами вершин заданными по часовой стрелке
bool DirectionFinderTest::find_direction_test_convex_polygon_clockwise_points()
{
    int expected = 1;

    std::vector<Point> points;

    points.push_back(Point {5.0, -2.0});
    points.push_back(Point {1.0, -5.0});
    points.push_back(Point {-3.5, -3.5});
    points.push_back(Point {-4.0, 3.0});
    points.push_back(Point {2.5, 3.5});

    DirectionFinder df(points);
    int result = df.find_direction();

    return result == expected;
}

void DirectionFinderTest::test()
{
    std::cout << "\n\tTesting \"DirectionFinder\" class:" << std::boolalpha

        << "\n\t\t"
        << find_direction_test_non_convex_polygon_anti_clockwise_points()
        << " --- \"find_direction()\" --- non-convex polygon + anti-clockwise points"
        << "\n\t\t"
        << find_direction_test_non_convex_polygon_clockwise_points()
        << " --- \"find_direction()\" --- non-convex polygon + clockwise points"
        << "\n\t\t"
        << find_direction_test_convex_polygon_anti_clockwise_points()
        << " --- \"find_direction()\" --- convex polygon + anti-clockwise points"
        << "\n\t\t"
        << find_direction_test_convex_polygon_clockwise_points()
        << " --- \"find_direction()\" --- convex polygon + clockwise points"
        << std::endl;
}









