#include "point_class.hpp"
#include "cross_product_class.hpp"
#include "direction_finder_class.hpp"

DirectionFinder::DirectionFinder(std::vector<Point> points):
    points_(points)
{ }

DirectionFinder::~DirectionFinder()
{
    //std::cout << "Destructor called for DirectionFinder" << std::endl;
}

void DirectionFinder::set_points(std::vector<Point> points)
{
    points_ = points;
}

std::vector<Point> DirectionFinder::get_points()
{
    return points_;
}

// сравнить суммы координат двух точек, чтобы найти точку с минимальными координатами в векторе
bool DirectionFinder::comparator(Point &p1, Point &p2)
{
    return p1.get_x() <= p2.get_x() && p1.get_y() < p2.get_y();
}

int DirectionFinder::find_direction()
{
    // поиск точки с минимальной координатой
    std::vector<Point>::iterator min_iter = std::min_element(points_.begin(), points_.end(), comparator);

    // левый и правый сосед минимальной точки
    std::vector<Point>::iterator left_neighbour, right_neighbour;

    if (min_iter == points_.begin())
    {
        // если первый элемент вектора

        left_neighbour = points_.end() - 1;
        right_neighbour = min_iter + 1;
    } 
    else if ((min_iter + 1) == points_.end())
    {
        // если последний элемент вектора

        left_neighbour = min_iter - 1;
        right_neighbour = points_.begin();
    } 
    else 
    {
        // если где-то посередине

        left_neighbour = min_iter - 1;
        right_neighbour = min_iter + 1;
    }

    CrossProduct cp_obj(*min_iter, *left_neighbour, *right_neighbour);
    double cp = cp_obj.compute();

    /* std::cout << "Min = " << ((Point) *min_iter).to_string() << "\n"
        << "Left neighbour = " << ((Point) *left_neighbour).to_string() << "\n"
        << "Right neighbour = " << ((Point) *right_neighbour).to_string() << "\n"
        << "Cross product = " << cp << std::endl; */

    if (cp > 0)
        return 1;
    return -1;
}
