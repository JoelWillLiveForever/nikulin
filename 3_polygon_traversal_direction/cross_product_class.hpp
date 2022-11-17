#pragma once

#include "point_class.hpp"

class CrossProduct
{
    private:
        Point p1_, p2_, p3_;

    public:
        CrossProduct();
        CrossProduct( Point p1, Point p2, Point p3 );

        ~CrossProduct();

        void set_points( Point p1, Point p2, Point p3 );
        std::vector<Point> get_points();

        void set_p1( Point p1 );
        Point get_p1();

        void set_p2( Point p2 );
        Point get_p2();

        void set_p3( Point p3 );
        Point get_p3();

        double compute();
        double compute( Point p1, Point p2, Point p3 ); // перегрузка метода compute()
};
