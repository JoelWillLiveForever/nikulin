#ifndef __DIRECTION_FINDER_HPP__
#define __DIRECTION_FINDER_HPP__

#include <vector>
#include "point.hpp"

class DirectionFinder
{
private:
    std::vector<Point> my_points;
    static bool comparator(Point &p1, Point &p2);

public:
    DirectionFinder(std::vector<Point> points);
    ~DirectionFinder();

    void set_points(std::vector<Point> points);
    std::vector<Point> get_points();

    int find_direction();
};

#endif
