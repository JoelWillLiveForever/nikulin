#pragma once

#include "stdafx.hpp"
#include "pi_monte_carlo_points_generator_class.hpp"

class PIConvergenceCheck
{
private:
    unsigned int total_pi_;             // количество создаваемых потоков и генераторов (кол-во рассчитываемых Пи)
    unsigned int points_start_;         // начальное количество точек для рассчёта (начало геометрической прогрессии)
    unsigned int points_multiplier_;    // множитель точек points_ += points_ * (points_multiplier - 1)
    unsigned int max_points_;           // сколько всего точек будет сгенерировано

    void thread_task(std::vector<PIMonteCarloPointsGenerator>::iterator generators_iter);    // метод, который будет выполняться в потоке

public:
    PIConvergenceCheck(unsigned int total_pi = 10, unsigned int points_start = 1'000, unsigned int points_multiplier = 10, unsigned int max_points = 10'000'000): 
        total_pi_(total_pi), points_start_(points_start), points_multiplier_(points_multiplier), max_points_(max_points)
    { }

    void set_total_pi(int total_pi) { total_pi_ = total_pi; }
    int get_total_pi() { return total_pi_; }

    void set_points_start(unsigned int points_start) { points_start_ = points_start; }
    unsigned int get_points_start() { return points_start_; }

    void set_points_multiplier(unsigned int points_multiplier) { points_multiplier_ = points_multiplier; }
    unsigned int get_points_multiplier() { return points_multiplier_; }

    void set_max_points(unsigned int max_points) { max_points_ = max_points; }
    unsigned int get_max_points() { return max_points_; }

    void convergence_check();   // проверка сходимости числа Пи

};
