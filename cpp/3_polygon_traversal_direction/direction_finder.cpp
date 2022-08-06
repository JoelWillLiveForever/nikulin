#include "direction_finder.hpp"
#include "cross_product.hpp"

#include <iostream>
#include <algorithm>

DirectionFinder::DirectionFinder(std::vector<Point> points):
    my_points(points)
{ }

DirectionFinder::~DirectionFinder()
{
    //std::cout << "Destructor called for DirectionFinder" << std::endl;
}

void DirectionFinder::set_points(std::vector<Point> points)
{
    my_points = points;
}

std::vector<Point> DirectionFinder::get_points()
{
    return my_points;
}

// сравнить суммы координат двух точек, чтобы найти точку с минимальными координатами в векторе
bool DirectionFinder::comparator(Point &p1, Point &p2)
{
    return p1.get_x() <= p2.get_x() && p1.get_y() < p2.get_y();
}

int DirectionFinder::find_direction()
{
    // поиск точки с минимальной координатой
    std::vector<Point>::iterator min_iter = std::min_element(my_points.begin(), my_points.end(), comparator);

    // левый и правый сосед минимальной точки
    std::vector<Point>::iterator left_neighbour, right_neighbour;

    if (min_iter == my_points.begin())
    {
        // если первый элемент вектора

        left_neighbour = my_points.end() - 1;
        right_neighbour = min_iter + 1;
    } 
    else if ((min_iter + 1) == my_points.end())
    {
        // если последний элемент вектора

        left_neighbour = min_iter - 1;
        right_neighbour = my_points.begin();
    } 
    else 
    {
        // если где-то посередине

        left_neighbour = min_iter - 1;
        right_neighbour = min_iter + 1;
    }

    CrossProduct cp_obj(*min_iter, *left_neighbour, *right_neighbour);
    double cp = cp_obj.compute();

    std::cout << "Min = " << ((Point) *min_iter).to_string() << "\n"
        << "Left neighbour = " << ((Point) *left_neighbour).to_string() << "\n"
        << "Right neighbour = " << ((Point) *right_neighbour).to_string() << "\n"
        << "Cross product = " << cp << std::endl; 

    if (cp > 0)
        return 1;
    return -1;
}
