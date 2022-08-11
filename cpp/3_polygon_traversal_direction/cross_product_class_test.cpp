#include "cross_product_class_test.hpp"

#include <iostream>

bool CrossProductTest::compute_test()
{
    double expected = -400.0;       // ожидаемый результат
    double eps = 0.01;              // допустимое расхождение между ожидаемым и полученным значениями

    Point p1(10.0, 10.0),
          p2(20.0, 20.0),
          p3(30.0, -10.0);

    CrossProduct cp(p1, p2, p3);
    double result = cp.compute();

    return std::fabs(expected - result) <= eps;
}

bool CrossProductTest::compute_ppp_test()
{
    double expected = 178.2;        // ожидаемый результат
    double eps = 0.01;              // допустимое расхождение между ожидаемым и полученным значениями

    Point p1(15.5, 37.0),
          p2(22.1, 45.2),
          p3(-10.9, 31.2);

    CrossProduct cp;
    double result = cp.compute(p1, p2, p3);

    return std::fabs(expected - result) <= eps;
}

void CrossProductTest::test()
{
    std::cout << "\n\tTesting \"CrossProduct\" class:" << std::boolalpha
        
        << "\n\t\t"
        << compute_test()
        << " --- \"compute()\""
        << "\n\t\t"
        << compute_ppp_test()
        << " --- \"compute(Point p1, Point p2, Point p3)\""
        << std::endl;
}
