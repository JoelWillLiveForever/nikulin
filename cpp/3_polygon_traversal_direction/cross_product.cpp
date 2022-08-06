#include "cross_product.hpp"
#include <iostream>

CrossProduct::CrossProduct(Point p1, Point p2, Point p3):
    my_p1(p1), my_p2(p2), my_p3(p3)
{ }

CrossProduct::~CrossProduct()
{
    //std::cout << "Destructor called for CrossProduct [" << my_p1.to_string()
    //    << ", " << my_p2.to_string()
    //    << ", " << my_p3.to_string()
    //    << "]" << std::endl;
}

void CrossProduct::set_points(Point p1, Point p2, Point p3)
{
    my_p1 = p1;
    my_p2 = p2;
    my_p3 = p3;
}

std::vector<Point> CrossProduct::get_points()
{
    std::vector<Point> result = {my_p1, my_p2, my_p3};
    return result;
}

void CrossProduct::set_p1(Point p1)
{
    my_p1 = p1;
}

Point CrossProduct::get_p1()
{
    return my_p1;
}

void CrossProduct::set_p2(Point p2)
{
    my_p2 = p2;
}

Point CrossProduct::get_p2()
{
    return my_p2;
}

void CrossProduct::set_p3(Point p3)
{
    my_p3 = p3;
}

Point CrossProduct::get_p3()
{
    return my_p3;
}

// функция для определения направления тройки векторов
// векторное произведение векторов (x2 - x1, y2 - y1), (x3 - x1, y3 - y1)
double CrossProduct::compute()
{
    return (my_p2.get_x() - my_p1.get_y())*(my_p3.get_y() - my_p1.get_y())
        - (my_p3.get_x() - my_p1.get_x())*(my_p2.get_y() - my_p1.get_y());
}
