/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

__kernel void boost(__global const uint *points, __global const uint *randoms, __global uint *good_points)
{    
    int id = get_global_id(0);
    good_points[id] = 0;

    uint rnd = id + points[id] + randoms[id];
    float x, y, length;

    for (int i = 1; i <= points[id]; i++)
    { 
        // генерация рандомных точек (их координат) в пределах 1/4 единичной окружности
        //rnd = (rnd * 73129 + 95121) % 100000;
       
        rnd ^= rnd << 13; // ещё немного рандома
        rnd ^= rnd >> 7;
        rnd ^= rnd << 17;
        
        x = (float) rnd / (float) UINT_MAX;

        rnd ^= rnd << 5;
        rnd ^= rnd >> 15;
        rnd ^= rnd << 21;

        y = (float) rnd / (float) UINT_MAX;

        length = sqrt(x*x + y*y); // расстояние от центра окружности до сгенерированной точки, если > 1, значит не принадлежит ей

        if (length <= 1.0)
            good_points[id]++;

        //good_points[id] = (float) rnd / (float) UINT_MAX;
    }

    //good_points[id] = 1000;    
}
