#include <stdio.h>
#include <stdlib.h>

#include "polygon_traversal_direction.hpp"

int main()
{
    float *x_source = {2, 4, 8, 10, 6};
    float *y_source = {1, 5, 6, 3, 0.5};

    int i = 5; // source size
    Node *head = NULL;
    do
    {
        push(head, x[i], y[i]);
    } while (i-- != 0);

    // создание односвязного списка с координатами точек и проверка на нулевой указатель
    list points = malloc(sizeof(list));
    if (!points)
    {
        printf("Allocation error!");
        return 1;
    }
    
    // заполняем список
    Node *head = NULL;


    // получить реузультат
    printf("Result = %d\n", get_traversal_direction(points));

    // чистим память
    free(points);
    return 0;
}
