#include "../include/true_pi_selector_class.hpp"

void TruePISelector::thread_task(std::vector<PIMonteCarloPointsGenerator>::iterator generators_iter)
{
    (*generators_iter).next();
}

double TruePISelector::select_pi()
{
    std::vector<std::thread> threads(total_pi_);
    std::vector<PIMonteCarloPointsGenerator> generators(total_pi_, PIMonteCarloPointsGenerator { points_start_ });

    // итераторы на векторы
    std::vector<std::thread>::iterator threads_iter = threads.begin();
    std::vector<PIMonteCarloPointsGenerator>::iterator generators_iter = generators.begin();
    
    // кол-во точек для генерации на текущей итерации
    unsigned int curr_points = points_start_;

    // находимся в цикле, пока не найдём Пи с нужной точностью
    while (1)
    {
        // запускаем потоки
        for (threads_iter = threads.begin(); threads_iter != threads.end(); threads_iter++)
            *threads_iter = std::thread { &TruePISelector::thread_task, this, generators.begin() + (threads_iter - threads.begin()) };
              
        // обновляем curr_points
        curr_points += curr_points * (points_multiplier_ - 1);

        // инициализируем min и max
        double min = DBL_MAX, max = DBL_MIN;

        // ожидаем пока все потоки закончат выполнение
        for (threads_iter = threads.begin(); threads_iter != threads.end(); threads_iter++)
        {
            (*threads_iter).join();

            generators_iter = generators.begin() + (threads_iter - threads.begin());        // получить итератор на нужный генератор
            double pi = (*generators_iter).get_pi();

            // обновить min и max
            if ( min > pi )
                min = pi;

            if ( max < pi )
                max = pi;
            
            // задать новое кол-во точек для рассчёта всем генераторам для следующей итерации
            (*generators_iter).set_n(curr_points);
        }
        
        // условие выхода из цикла    
        double e = max - min;
        if (e < eps_)
            break;
    }

    return (*generators_iter).get_pi();
}
