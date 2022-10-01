#include "counters.h"

struct PIPoints
{
    uint64_t good_points;
    uint64_t all_points;
};

void generate_points(struct PIPoints *pi_points_arr,
        uint32_t index,
        uint32_t how_much_to_gen,
        bool use_xs_1024)
{
    if (!pi_points_arr) // проверка на нулевой указатель
    {
        fprintf(stderr, "Bad pointer for \"pi_points_arr\" in module \'counters.c\'\n");
        exit(EXIT_FAILURE);
    }

    pi_points_arr[index].all_points += how_much_to_gen;

    double x, y;
    uint8_t len;
    
    while (how_much_to_gen--)
    {
        if ( use_xs_1024 )
        {
            x = next(0, 1);
            y = next(0, 1);
        }
        else
        {
            x = next(0, 0);
            y = next(0, 0);
        }

        len = x*x + y*y;
        pi_points_arr[index].good_points += (!len);
    }

    //return 4.0 * (double)(*pi_points).good_points / (double)(*pi_points).all_points;
}

double get_pi_single_thread(uint8_t number_of_counters,
        uint32_t start,
        uint32_t multiplier,
        double eps,
        bool use_xs1024)
{
    struct PIPoints *pi_points_arr = calloc(number_of_counters, sizeof(*pi_points_arr));
    uint32_t i;

    double min_pi, max_pi, pi;

    while (1)
    {
        min_pi = DBL_MAX;
        max_pi = DBL_MIN;

        for (i = 0; i < number_of_counters; i++)
        {
            generate_points(pi_points_arr, i, start, use_xs1024);
            pi = 4.0 * (double) pi_points_arr[i].good_points / (double) pi_points_arr[i].all_points;

            if (min_pi > pi)
                min_pi = pi;

            if (max_pi < pi)
                max_pi = pi;
        }

        double e = max_pi - min_pi;
        //printf("eps: %f\n", e);

        if (e < eps)
            break;

        //printf("%f\n", pi);
        //printf("Start: %u\n", start);

        start *= multiplier;
    }

    printf("All generated points: %llu\n", pi_points_arr->all_points);
    return pi;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// реализация версии multithread

struct ThreadArgs
{
    struct PIPoints *pi_points_arr;
    
    unsigned *indexes;
    unsigned indexes_size;

    unsigned how_much_points_to_gen;

    bool use_xs1024;
};

//pthread_mutex_t locker;

void *generate_points_in_thread(void *thread_args)
{
    struct ThreadArgs *args = (struct ThreadArgs *) thread_args;
    
    if ( !args )
        return NULL;

    struct PIPoints *pi_points_arr = (struct PIPoints *) args->pi_points_arr;
    
    unsigned *indexes = (unsigned *) args->indexes;
    unsigned indexes_size = (unsigned) args->indexes_size;

    unsigned how_much_to_gen = (unsigned) args->how_much_points_to_gen;

    bool use_xs1024 = (bool) args->use_xs1024;

    uint64_t *bank_numbers = (uint64_t *) calloc(16, sizeof(uint64_t));
    
    uint32_t bank_index = 0;
    uint32_t *pointer_to_bank_index = &bank_index;

    uint64_t xs64_value = 0;
    uint64_t *pointer_to_xs64_value = &xs64_value;

    for ( int i = 0; i < indexes_size; i++ )
    {
        unsigned index = indexes[i];

        pi_points_arr[index].all_points += how_much_to_gen;
    
        double x, y;
        uint8_t len;
        
        unsigned counter = how_much_to_gen;

        while (counter--)
        {
            if ( use_xs1024 )
            {
                x = next_thread_safe(0, 1, pointer_to_xs64_value, bank_numbers, pointer_to_bank_index);
                y = next_thread_safe(0, 1, pointer_to_xs64_value, bank_numbers, pointer_to_bank_index);
            }
            else
            {
                x = next_thread_safe(0, 0, pointer_to_xs64_value, bank_numbers, pointer_to_bank_index);
                y = next_thread_safe(0, 0, pointer_to_xs64_value, bank_numbers, pointer_to_bank_index);
            }
    
            len = x*x + y*y;
            pi_points_arr[index].good_points += (!len);
        }
    }

    return NULL;
}

double get_pi_multithread(unsigned number_of_counters,
        unsigned start,
        unsigned multiplier,
        double eps,
        unsigned number_of_processors,
        bool use_xs1024)
{
//    printf("number_of_counters: %u\n"
//            "start: %u\n"
//            "multiplier: %u\n"
//            "eps: %f\n"
//            "number_of_processors: %u\n"
//            "use_xs_1024: %b\n",
//            
//            number_of_counters, start, multiplier, eps, number_of_processors, use_xs1024);    
    
    struct PIPoints *pi_points_arr = (struct PIPoints *) calloc(number_of_counters, sizeof(struct PIPoints));
    double pi;

    // разбить pi_points_arr на части и распределить эти части между потоками
    struct ThreadArgs *thread_args = (struct ThreadArgs *) calloc(number_of_processors, sizeof(struct ThreadArgs));
    for (int i = 0; i < number_of_processors; i++)
    {
        thread_args[i].how_much_points_to_gen = start;  // установить кол-во точек для генерации

        thread_args[i].pi_points_arr = pi_points_arr;
        unsigned len = 0;

        for (int j = i; j < number_of_counters; j += number_of_processors)
        {
            if ( thread_args[i].indexes )
                thread_args[i].indexes = (unsigned *) realloc(thread_args[i].indexes, (++len) * sizeof(unsigned)); // расширяем динамический массив
            else
                thread_args[i].indexes = (unsigned *) calloc(++len, sizeof(unsigned));
            
            thread_args[i].indexes[len - 1] = j;
        }

        thread_args[i].indexes_size = len;
        thread_args[i].use_xs1024 = use_xs1024;
    }

    // создаём массив потоков
    pthread_t threads[number_of_processors];
    int err;

    // находимся в цикле, пока Пи не достигнет заданной точности
    while (1)
    {
        // запускаем потоки на выполнение
        for ( int i = 0; i < number_of_processors; i++ )
        {
            //printf("Creating thread: %d\n", i);
            err = pthread_create( &threads[i], NULL, generate_points_in_thread, (void *) &thread_args[i] );
            
            if (err)
            {
                fprintf(stderr, "Error! Unable to create thread: %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
    
        // ожидаем пока потоки закончат выполнение
        for ( int i = 0; i < number_of_processors; i++ )
            pthread_join(threads[i], NULL);
    
        // вычисление Пи, поиск Min Max и рассчёт eps
        double min_pi = DBL_MAX,
               max_pi = DBL_MIN;
    
        for ( int i = 0; i < number_of_counters; i++ )
        {
            pi = 4.0 * (double) pi_points_arr[i].good_points / (double) pi_points_arr[i].all_points;
    
            if ( min_pi > pi )
                min_pi = pi;
    
            if ( max_pi < pi )
                max_pi = pi;

//            printf("\npi_points_arr[%u].good_points: %u\n"
//                    "pi_points_arr[%u].all_points: %u\n"
//                    "pi_points_arr[%u].pi: %f\n",
//                     
//                    i, pi_points_arr[i].good_points, i, pi_points_arr[i].all_points, i, pi);
        }
    
        double e = max_pi - min_pi;

//        printf("\n\npi: %f\n", pi);
//        printf("e: %f\n\n", e);
    
        if ( e < eps )
            break;

        start *= multiplier;

        // обновляем how_much_to_gen у всех потоков
        for ( int i = 0; i < number_of_processors; i++ )
            thread_args[i].how_much_points_to_gen = start;
    }

    return pi;
}
