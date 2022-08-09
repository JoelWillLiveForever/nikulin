#include "pi_monte_carlo_points_generator_class.hpp"

void PIMonteCarloPointsGenerator::next()
{
	// генератор псевдослучайных чисел из библиотеки <random>
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    ap += n_;                       // увеличить общее количество точек
    double x = 0, y = 0, len = 0;   // координаты точки и её расстояние до центра окружности
    
    unsigned int counter = 0;
    while (counter < n_)
    {
        // сгенерируем координаты точки
        x = dist(gen);
        y = dist(gen);
        
        len = x*x + y*y;

        // точка входит в круг
        if (len <= 1.0) 
            gp++; // хорошие точки

        counter++;
    }

    pi_ = 4.0 * static_cast<double>(gp) / static_cast<double>(ap);   // значение Пи на основе сгенерированных точек
}

double PIMonteCarloPointsGenerator::get_pi()
{
    return pi_;
}
