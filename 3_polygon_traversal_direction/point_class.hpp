#pragma once

class Point
{
    private:
        double my_x, my_y;

    public:
        Point( double x, double y ); // конструктор
        ~Point();                   // деструктор

        void set_x( double x );
        double get_x();

        void set_y( double y );
        double get_y();

        std::string to_string();    // если нужно вывести координаты точки на экран
};
