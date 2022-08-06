#ifndef __CROSS_PRODUCT_HPP__
#define __CROSS_PRODUCT_HPP__

#include "point.hpp"
#include <vector>

class CrossProduct
{
private:
    Point my_p1, my_p2, my_p3;

public:
    CrossProduct(Point p1, Point p2, Point p3);
    ~CrossProduct();
    
    void set_points(Point p1, Point p2, Point p3);
    std::vector<Point> get_points();

    void set_p1(Point p1);
    Point get_p1();

    void set_p2(Point p2);
    Point get_p2();

    void set_p3(Point p3);
    Point get_p3();

    double compute();
};

#endif
