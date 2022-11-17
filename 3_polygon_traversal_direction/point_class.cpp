#include "point_class.hpp"

Point::Point( double x, double y ):
    my_x( x ), my_y( y )
{ }

Point::~Point()
{
    // std::cout << "Destructor called for Point {" << my_x << "; " << my_y << "}" << std::endl;
}

void Point::set_x( double x )
{
    my_x = x;
}

double Point::get_x()
{
    return my_x;
}

void Point::set_y( double y )
{
    my_y = y;
}

double Point::get_y()
{
    return my_y;
}

std::string Point::to_string()
{
    return "{" + std::to_string( my_x ) + "; " + std::to_string( my_y ) + "}";
}
