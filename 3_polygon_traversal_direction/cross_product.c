#include "foo.h"

// функция для определения направления тройки векторов
// векторное произведение векторов (x2 - x1, y2 - y1), (x3 - x1, y3 - y1)
double cross_product(float x1, float y1, float x2, float y2, float x3, float y3)
{
    return (double) (x2 - x1)*(y3 - y1) - (double)(x3 - x1)*(y2 - y1);
}
