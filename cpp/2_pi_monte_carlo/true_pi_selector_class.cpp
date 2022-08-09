#include "true_pi_selector_class.hpp"

void TruePISelector::thread_task(int thread_id)
{
    generators[thread_id].next();
}

double TruePISelector::select_pi()
{
    generators = new PIMonteCarloPointsGenerator[total_];
    std::thread threads[total_];

    bool isTrue = true;
    int i;
    
    // каждый генератор генерирует по 2000 точек
    for (i = 0; i < total_; i++)
        generators[i] = PIMonteCarloPointsGenerator { 2000 };
    
    // находимся в цикле, пока по всем потокам (по их Пи) не будет совпадения до нужного числа знаков (0.0001)
    while (isTrue)
    {
        // запускаем потоки
        for (i = 0; i < total_; i++)
            threads[i] = std::thread { &TruePISelector::thread_task, this, i };
    
        std::cout << "\nThreads:";
        std::cout.precision(6);

        // ожидаем пока все потоки закончат выполнение
        for (i = 0; i < total_; i++)
        {
            threads[i].join();

            std::cout << std::fixed << std::right << " [" << i << "] = " << generators[i].get_pi();
        }

        // значения всех рассчитанных Пи должны совпадать с заданной точностью
        int pi_0_int = static_cast<int>(generators[0].get_pi() / eps_ / 10.0);
        int pi_curr_int;

        for (i = 1; i < total_; i++)
        {
            // выделяем нужную дробную часть, остальную отбрасываем
            pi_curr_int = static_cast<int>(generators[i].get_pi() / eps_ / 10.0);

            // если есть несовпадение, выходим из цикла и считаем Пи дальше в потоках
            if ( pi_0_int != pi_curr_int )
                break;

            // если у всех Пи знаки совпадают (если все Пи во всех потоках одинаковы), это и будет истинным Пи -> выводим ответ пользователю
            if (i == total_ - 1)
               isTrue = false; 
        }

    }

    return generators[0].get_pi();
}
