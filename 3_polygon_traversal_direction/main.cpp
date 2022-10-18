/* Условие задачи 3:
* Выпуклый многоугольник задаётся координатами вершин при обходе по часовой или против часовой стрелки.
* Контур многоугольника не имеет самопересечений.
* Определить направление обхода.
* Выполнить то же самое, но только в случае невыпуклого многоугольника. */

#include "../pch.hpp"

#include "direction_finder_class.hpp"
#include "point_class.hpp"

int main()
{
    int amount_of_points;                                           // количество точек

    std::ifstream infile;                                           // создать объект ifstream    
    infile.open("polygon_traversal_direction_source.txt", std::ios::in);                        // открыть файл source.txt в режиме чтения

    if ( !infile )
    {
        std::cout << "Error! File bad or empty!" << std::endl;
        return EXIT_FAILURE;
    }

    infile >> amount_of_points;                                     // узнать количество точек из файла
    std::vector<Point> points;                                      // объявляем вектор для точек

    // читаем координаты точек из файла
    double x, y;
    int i;

    for (i = 0; i < amount_of_points * 2; i++)
    {
        if ( infile.eof() && i < amount_of_points * 2 )
        {
            // если количество координат не соответствует количеству точек, то ошибка
            std::cout << "Error! The number of coordinates doesn't match the number of points!" << std::endl;
            return EXIT_FAILURE;
        }

        if (i % 2 == 0) 
        {
            // координата x
            infile >> x;
        }
        else
        {
            // координата y
            infile >> y;

            Point p(x, y);
            points.push_back(p);
        }
    }
    
    // смотрим на прочитанные координаты
    std::vector<Point>::iterator iter = points.begin();
    while (iter != points.end())
    {
        std::cout << "Element: " << ((Point) *iter).to_string() << std::endl;
        iter++;
    }

    DirectionFinder df(points);
    int result = df.find_direction();     

    result == -1
        ? std::cout << "Result = " << result << "; (anti-clockwise)" << std::endl
        : std::cout << "Result = " << result << "; (clockwise)" << std::endl;
    
    return 0;
}
