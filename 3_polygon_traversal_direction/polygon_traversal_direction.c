#include "foo.h"

int get_traversal_direction(float *x_source, float *y_source, int size)
{
    int i, min_index = 0;
    float min_x = x_source[0], min_y = y_source[0];
    for (i = 0; i < size; i++)
    {
        if (x_source[i] < min_x 
                || (x_source[i] == min_x && y_source[i] < min_y))
        {
            min_index = i;

            min_x = x_source[i];
            min_y = y_source[i];
        }
    }

    // левый сосед
    float min_x_left_neighbour = x_source[(min_index + size - 1) % size], 
          min_y_left_neighbour = y_source[(min_index + size - 1) % size];

    // правый сосед
    float min_x_right_neighbour = x_source[(min_index + 1) % size],
          min_y_right_neighbour = y_source[(min_index + 1) % size];

    //printf("min_index = %d;\n", min_index);
    //printf("min_x = %f; min_y = %f;\n", min_x, min_y);
    //printf("min_x_left_neighbour = %f; min_y_left_neighbour = %f;\n", min_x_left_neighbour, min_y_left_neighbour);
    //printf("min_x_right_neighbour = %f; min_y_right_neighbour = %f;\n", min_x_right_neighbour, min_y_right_neighbour);

    // векторное произведение
    // если левая тройка, то обход по часовой стрелке
    // если правая тройка, то обход против часовой стрелки
    double cp = cross_product(min_x, min_y, min_x_left_neighbour, min_y_left_neighbour, min_x_right_neighbour, min_y_right_neighbour);

    //printf("cross product = %f;\n", cp);

    if (cp > 0) 
        return 1;
    return -1;
}
