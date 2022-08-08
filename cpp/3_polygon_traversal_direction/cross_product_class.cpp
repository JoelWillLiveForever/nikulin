#include "cross_product_class.hpp"

#include <iostream>

CrossProduct::CrossProduct():
    p1_(0, 0), p2_(0, 0), p3_(0, 0)
{ }

CrossProduct::CrossProduct(Point p1, Point p2, Point p3):
    p1_(p1), p2_(p2), p3_(p3)
{ }

CrossProduct::~CrossProduct()
{
    //std::cout << "Destructor called for CrossProduct [" << p1_.to_string()
    //    << ", " << p2_.to_string()
    //    << ", " << p3_.to_string()
    //    << "]" << std::endl;
}

void CrossProduct::set_points(Point p1, Point p2, Point p3)
{
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
}

std::vector<Point> CrossProduct::get_points()
{
    std::vector<Point> result = {p1_, p2_, p3_};
    return result;
}

void CrossProduct::set_p1(Point p1)
{
    p1_ = p1;
}

Point CrossProduct::get_p1()
{
    return p1_;
}

void CrossProduct::set_p2(Point p2)
{
    p2_ = p2;
}

Point CrossProduct::get_p2()
{
    return p2_;
}

void CrossProduct::set_p3(Point p3)
{
    p3_ = p3;
}

Point CrossProduct::get_p3()
{
    return p3_;
}

// функция для определения направления тройки векторов
// векторное произведение векторов (x2 - x1, y2 - y1), (x3 - x1, y3 - y1)
double CrossProduct::compute()
{
    return (p2_.get_x() - p1_.get_x()) * (p3_.get_y() - p1_.get_y())
        - (p2_.get_y() - p1_.get_y()) * (p3_.get_x() - p1_.get_x());
}

double CrossProduct::compute(Point p1, Point p2, Point p3)
{
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
    
    return (p2_.get_x() - p1_.get_x()) * (p3_.get_y() - p1_.get_y())
        - (p2_.get_y() - p1_.get_y()) * (p3_.get_x() - p1_.get_x());
}
