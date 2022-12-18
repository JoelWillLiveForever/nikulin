#pragma once

#include "pi_monte_carlo_points_generator_class.hpp"

class PIConvergenceCheck
{
private:
    std::shared_ptr<spdlog::logger> logger;

    unsigned int total_pi_;             // количество создаваемых потоков и генераторов (кол-во рассчитываемых Пи)
    unsigned int points_start_;         // начальное количество точек для рассчёта (начало геометрической прогрессии)
    unsigned int points_multiplier_;    // множитель точек points_ += points_ * (points_multiplier - 1)
    unsigned int max_points_;           // сколько всего точек будет сгенерировано

    double eps_;                        // заданная точность

    void thread_task(std::vector<PIMonteCarloPointsGenerator>::iterator generators_iter);    // метод, который будет выполняться в потоке

public:
    PIConvergenceCheck(const std::string& program_name, unsigned int total_pi = 10, unsigned int points_start = 1'000,
                       unsigned int points_multiplier = 10, unsigned int max_points = 10'000'000, double eps = 0.0001):
                       total_pi_(total_pi), points_start_(points_start), points_multiplier_(points_multiplier),
                       max_points_(max_points), eps_(eps)
    {
//        try
//        {
//            extern std::string program_name;
            logger = spdlog::rotating_logger_mt("PIConvergenceCheck.class", program_name, 1024 * 1024 * 5, 3);
            logger->flush_on( spdlog::level::trace );
//        }
//        catch (const spdlog::spdlog_ex& ex)
//        {
//            std::cout << "Log initialization failed: " << ex.what() << std::endl;
//            exit(EXIT_FAILURE);
//        }
        logger->info("Logger init");
    }

    void set_total_pi(int total_pi) { total_pi_ = total_pi; }
    int get_total_pi() { return total_pi_; }

    void set_points_start(unsigned int points_start) { points_start_ = points_start; }
    unsigned int get_points_start() { return points_start_; }

    void set_points_multiplier(unsigned int points_multiplier) { points_multiplier_ = points_multiplier; }
    unsigned int get_points_multiplier() { return points_multiplier_; }

    void set_max_points(unsigned int max_points) { max_points_ = max_points; }
    unsigned int get_max_points() { return max_points_; }

    void set_eps(double eps) { eps_ = eps; }
    double get_eps() { return eps_; }

    void convergence_check();   // проверка сходимости числа Пи

};
