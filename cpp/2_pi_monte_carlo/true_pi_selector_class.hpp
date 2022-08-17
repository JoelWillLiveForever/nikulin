#pragma once

#include "stdafx.hpp"
#include "pi_monte_carlo_points_generator_class.hpp"

class TruePISelector
{
private:
    int total_;                                 // количество создаваемых потоков и генераторов
    double eps_;                                // необходимая точность рассчёта Пи

    PIMonteCarloPointsGenerator *generators;    // генераторы Пи

    void thread_task(int thread_id);            // метод, который будет выполняться в потоке

public:
    TruePISelector(): total_(5), eps_(0.0001) { }
    TruePISelector(int total, double eps): total_(total), eps_(eps) { }

    void set_total(int total) { total_ = total; }
    int get_total() { return total_; }

    void set_eps(double eps) { eps_ = eps; }
    double get_eps() { return eps_; }

    double select_pi();                         // рассчёт Пи

};
