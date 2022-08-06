#include "polygon_traversal_direction.hpp"

long Det(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return (long) (x2 - x1)*(y3 - y1) - (long)(y2 - y1)*(x3 - x1);
}

int get_traversal_direction(list points)
{
    list ptr = points, 
         prev = points, 
         min = points, 
         min_p = points;

    while (prev->next != points)
    {
        if (ptr->x < min->x)
        {
            min = ptr;
            min_p = prev;
        }
        
        prev = ptr;
        ptr = ptr->next;
    }

    if (min == points)
        while (min_p->next != min)
            min_p = min_p->next;

    if (Det(min->x, min->y, min_p->x, min_p->y, min->next->x, min->next->y) > 0)
        return 1;
    return -1;
}
