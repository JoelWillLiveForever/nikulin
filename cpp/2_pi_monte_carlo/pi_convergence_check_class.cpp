#include "pi_convergence_check_class.hpp"

void PIConvergenceCheck::thread_task(std::vector<PIMonteCarloPointsGenerator>::iterator generators_iter)
{
    (*generators_iter).next();
}

void PIConvergenceCheck::convergence_check()
{
    std::vector<std::thread> threads(total_pi_);   // вектор потоков
    std::vector<PIMonteCarloPointsGenerator> generators(total_pi_, PIMonteCarloPointsGenerator { points_start_ });

    // получаем итераторы на векторы
    std::vector<std::thread>::iterator threads_iter = threads.begin();
    std::vector<PIMonteCarloPointsGenerator>::iterator generators_iter = generators.begin();

    unsigned int curr_points = points_start_;
    double prev_avg = -1;

    do
    {
        // запускаем потоки
        for (threads_iter = threads.begin(); threads_iter != threads.end(); threads_iter++)
            *threads_iter = std::thread { &PIConvergenceCheck::thread_task, this, generators.begin() + (threads_iter - threads.begin()) };
        
        // инициализируем min и max
        double min = DBL_MAX, max = DBL_MIN, avg = 0;

        unsigned int prev_points = curr_points;
        curr_points += curr_points * (points_multiplier_ - 1);

        // ожидаем пока все потоки закончат выполнение
        for (threads_iter = threads.begin(); threads_iter != threads.end(); threads_iter++)
        {
            (*threads_iter).join();

            generators_iter = generators.begin() + (threads_iter - threads.begin());        // рассчитать итератор нужного генератора
            double pi = (*generators_iter).get_pi();

            // определить min и max на данной итерации
            if ( min > pi )
                min = pi;

            if ( max < pi )
                max = pi;

            // рассчёт среднего
            avg += pi;
            
            // задать новое кол-во точек для рассчёта всем генераторам для следующей итерации
            (*generators_iter).set_n(curr_points);
        }

        double eps = max - min;
        avg /= total_pi_;

        if (prev_avg == -1)
            std::cout << "For " << prev_points << " points: " << "MinPI = " << min << "; MaxPI = " << max << "; AvgPI = " << avg << "; E = " << eps << '\n';
        else
            std::cout << "For " << prev_points << " points: " << "MinPI = " << min << "; MaxPI = " << max << "; AvgPI = " << avg << "; E = " << eps << "; E2 = " << fabs(avg - prev_avg) << '\n';

        prev_avg = avg;
    }
    while ( (*generators_iter).get_all_points() < max_points_ );
}
