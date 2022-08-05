/* Условие задачи 2:
 * Вычислить значение числа Пи методом Монте-Карло с точностью 0.0001 */

#include <iostream>
//#include <time>
#include <cmath>
#include <random>

using namespace std;

#define EPS 0.0001 // точность, c которой нужно найти число Пи

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 1.0);
      
    cout << "unsigned long long = " << sizeof(unsigned long long) 
        << "\nunsigned long = " << sizeof(unsigned long)
        << "\nunsigned int = " << sizeof(unsigned int)
        << endl;

    cout << "long double = " << sizeof(long double)
        << "\ndouble = " << sizeof(double)
        << endl;

    unsigned long long gp = 0, ap = 0; // хорошие точки и всего точек, соответственно

    double x = 0, y = 0, len = 0; // координаты точки и её расстояние до центра окружности
    double prev_pi = -1, curr_pi = 0, e = 1; // предыдущее Пи, текущее Пи и их разность

    // считаем пи, пока не добъёмся нужной точности
    do
    {
        ap++; // считаем всего точек 

        // сгенерируем координаты точки
        x = dist(gen);
        y = dist(gen);
           
        len = x*x + y*y; // расстояние до центра окружности

        // точка входит в круг
        if (len <= 1.0) gp++; // хорошие точки
        
        if (ap % 1'000'000 == 0) // раз в 1 000 000 точек сравнить значения Пи, чтобы проверить удовлетворение точности EPS
        {            
            prev_pi = curr_pi;

            curr_pi = 4.0 * (long double) gp / (long double) ap; // вычисляем Пи
            
            e = fabs(curr_pi - prev_pi); // разница между прошлым Пи и текущим Пи (точность)
                                         
            // вывод информации с итерации
            cout << "prev_pi = " << prev_pi
                << " curr_pi = " << curr_pi
                << " eps = " << e
                << " gp = " << gp
                << " ap = " << ap
                << endl;
        }
    } 
    while (e > EPS); // как только разница между прошлым Пи и текущим Пи будет > EPS, выйти из цикла

    // вывод рассчитанного Пи
    cout << "PI = " << curr_pi << endl;
    return 0;
}
