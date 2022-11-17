#include "counters.h"

struct PIPoints
{
    uint64_t good_points;
    uint64_t all_points;
};

void generate_points( struct PIPoints *pi_points_arr,
                      uint32_t index,
                      uint32_t how_much_to_gen,
                      bool use_xs_1024 )
{
    if ( !pi_points_arr ) // проверка на нулевой указатель
    {
        fprintf( stderr, "Bad pointer for \"pi_points_arr\" in module \'counters.c\'\n" );
        exit( EXIT_FAILURE );
    }

    ( pi_points_arr + index )->all_points += how_much_to_gen;

    double x, y;
    uint8_t len;

    while ( how_much_to_gen-- )
    {
        if ( use_xs_1024 )
        {
            x = next_xs1024( 0 ) / ( double )RANDOM_MAX;
            y = next_xs1024( 0 ) / ( double )RANDOM_MAX;
        }
        else
        {
            x = next_xs64( 0 ) / ( double )RANDOM_MAX;
            y = next_xs64( 0 ) / ( double )RANDOM_MAX;
        }

        len = ( uint8_t )( x * x + y * y );
        ( pi_points_arr + index )->good_points += ( !len );
    }

    //return 4.0 * (double)(*pi_points).good_points / (double)(*pi_points).all_points;
}

double get_pi_single_thread( long number_of_counters,
                             uint32_t start,
                             uint32_t multiplier,
                             double eps,
                             bool use_xs1024 )
{
    struct PIPoints *pi_points_arr = calloc( number_of_counters, sizeof( *pi_points_arr ) );

    if ( pi_points_arr != NULL )
    {
        long i;

        double min_pi, max_pi, pi;

        while ( 1 )
        {
            min_pi = DBL_MAX;
            max_pi = DBL_MIN;
            pi = -1;

            for ( i = 0; i < number_of_counters; i++ )
            {
                generate_points( pi_points_arr, i, start, use_xs1024 );
                pi = 4.0 * ( pi_points_arr + i )->good_points / ( double )( pi_points_arr + i )->all_points;

                /* pi = 4.0 * pi_points_arr[i].good_points / (double)pi_points_arr[i].all_points;*/

                if ( min_pi > pi )
                    min_pi = pi;

                if ( max_pi < pi )
                    max_pi = pi;
            }

            double e = max_pi - min_pi;
            //printf("eps: %f\n", e);

            if ( e < eps )
                break;

            //printf("%f\n", pi);
            //printf("Start: %u\n", start);

            start *= multiplier;
        }

        return pi;
    }
    else
        return -1;
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

void *generate_points_in_thread( void *thread_args )
{
    struct ThreadArgs *args = ( struct ThreadArgs * )thread_args;

    if ( !args )
        return NULL;

    struct PIPoints *pi_points_arr = ( struct PIPoints * )args->pi_points_arr;

    unsigned *indexes = ( unsigned * )args->indexes;
    unsigned indexes_size = ( unsigned )args->indexes_size;

    unsigned how_much_to_gen = ( unsigned )args->how_much_points_to_gen;

    bool use_xs1024 = ( bool )args->use_xs1024;

    uint64_t *bank_numbers = ( uint64_t * )calloc( 16, sizeof( uint64_t ) );

    uint32_t bank_index = 0;
    uint64_t xs64_value = 0;

    for ( unsigned i = 0; i < indexes_size; i++ )
    {
        unsigned index = indexes[i];

        pi_points_arr[index].all_points += how_much_to_gen;

        double x, y;
        uint8_t len;

        unsigned counter = how_much_to_gen;

        while ( counter-- )
        {
            if ( use_xs1024 )
            {
                x = next_xs1024_thread_safe( 0, &xs64_value, bank_numbers, &bank_index ) / ( double )RANDOM_MAX;
                y = next_xs1024_thread_safe( 0, &xs64_value, bank_numbers, &bank_index ) / ( double )RANDOM_MAX;
            }
            else
            {
                x = next_xs64_thread_safe( 0, &xs64_value ) / ( double )RANDOM_MAX;
                y = next_xs64_thread_safe( 0, &xs64_value ) / ( double )RANDOM_MAX;
            }

            len = ( uint8_t )( x * x + y * y );
            pi_points_arr[index].good_points += ( !len );
        }
    }

    return NULL;

}

double get_pi_multithread( long number_of_counters,
                           unsigned start,
                           unsigned multiplier,
                           double eps,
                           unsigned number_of_processors,
                           bool use_xs1024 )
{
    #if 0
    //    printf("number_of_counters: %u\n"
    //            "start: %u\n"
    //            "multiplier: %u\n"
    //            "eps: %f\n"
    //            "number_of_processors: %u\n"
    //            "use_xs_1024: %b\n",
    //
    //            number_of_counters, start, multiplier, eps, number_of_processors, use_xs1024);
    struct PIPoints *pi_points_arr = ( struct PIPoints * ) calloc( number_of_counters, sizeof( struct PIPoints ) );
    double pi = -1;

    // разбить pi_points_arr на части и распределить эти части между потоками
    struct ThreadArgs *thread_args = ( struct ThreadArgs * ) calloc( number_of_processors, sizeof( struct ThreadArgs ) );

    for ( unsigned i = 0; i < number_of_processors; i++ )
    {
        thread_args[i].how_much_points_to_gen = start;  // установить кол-во точек для генерации

        thread_args[i].pi_points_arr = pi_points_arr;
        unsigned len = 0;

        for ( long j = i; j < number_of_counters; j += number_of_processors )
        {
            len++;

            if ( thread_args[i].indexes )
            {
                unsigned *temp = ( unsigned * )realloc( thread_args[i].indexes, len * sizeof( unsigned ) );

                if ( temp != NULL )
                    *thread_args[i].indexes = *temp; // расширяем динамический массив
            }
            else
                thread_args[i].indexes = ( unsigned * )calloc( len, sizeof( unsigned ) );

            if ( ( thread_args[i].indexes + len - 1 ) != NULL )
                *( thread_args[i].indexes + len - 1 ) = j;
        }

        thread_args[i].indexes_size = len;
        thread_args[i].use_xs1024 = use_xs1024;
    }

    // создаём массив потоков
    pthread_t *threads = malloc( number_of_processors * sizeof( pthread_t ) );

    if ( threads )
    {
        int err;

        // находимся в цикле, пока Пи не достигнет заданной точности
        while ( 1 )
        {
            // запускаем потоки на выполнение
            for ( unsigned i = 0; i < number_of_processors; i++ )
            {
                //printf("Creating thread: %d\n", i);
                err = pthread_create( &threads[i], NULL, generate_points_in_thread, ( void * )&thread_args[i] );

                if ( err )
                {
                    fprintf( stderr, "Error! Unable to create thread: %d\n", i );
                    exit( EXIT_FAILURE );
                }
            }

            // ожидаем пока потоки закончат выполнение
            for ( unsigned i = 0; i < number_of_processors; i++ )
                pthread_join( threads[i], NULL );

            // вычисление Пи, поиск Min Max и рассчёт eps
            double min_pi = DBL_MAX,
                   max_pi = DBL_MIN;

            for ( long i = 0; i < number_of_counters; i++ )
            {
                pi = 4.0 * ( double )pi_points_arr[i].good_points / ( double )pi_points_arr[i].all_points;

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
            for ( unsigned i = 0; i < number_of_processors; i++ )
                thread_args[i].how_much_points_to_gen = start;
        }

        return pi;
    }
    else
        return -1;

    #else
    //    printf("number_of_counters: %u\n"
    //            "start: %u\n"
    //            "multiplier: %u\n"
    //            "eps: %f\n"
    //            "number_of_processors: %u\n"
    //            "use_xs_1024: %b\n",
    //
    //            number_of_counters, start, multiplier, eps, number_of_processors, use_xs1024);
    struct PIPoints *pi_points_arr = ( struct PIPoints * )calloc( number_of_counters, sizeof( struct PIPoints ) );
    double pi = -1;

    // разбить pi_points_arr на части и распределить эти части между потоками
    struct ThreadArgs *thread_args = ( struct ThreadArgs * )calloc( number_of_processors, sizeof( struct ThreadArgs ) );

    for ( unsigned i = 0; i < number_of_processors; i++ )
    {
        thread_args[i].how_much_points_to_gen = start;  // установить кол-во точек для генерации

        thread_args[i].pi_points_arr = pi_points_arr;
        unsigned len = 0;

        for ( int j = i; j < number_of_counters; j += number_of_processors )
        {
            if ( thread_args[i].indexes )
            {
                unsigned *temp = ( unsigned * )realloc( thread_args[i].indexes,
                                                        ( ++len ) * sizeof( unsigned ) ); // расширяем динамический массив

                if ( temp )
                    thread_args[i].indexes = temp;
            }
            else
                thread_args[i].indexes = ( unsigned * )calloc( ++len, sizeof( unsigned ) );

            ( *( thread_args[i].indexes + len - 1 ) ) = j;
        }

        thread_args[i].indexes_size = len;
        thread_args[i].use_xs1024 = use_xs1024;
    }

    // создаём массив потоков
    pthread_t *threads = malloc( number_of_processors * sizeof( pthread_t ) );
    int err = 0;

    // находимся в цикле, пока Пи не достигнет заданной точности
    while ( 1 )
    {
        // запускаем потоки на выполнение
        for ( unsigned i = 0; i < number_of_processors; i++ )
        {
            //printf("Creating thread: %d\n", i);
            if ( threads )
                err = pthread_create( &threads[i], NULL, generate_points_in_thread, ( void * )&thread_args[i] );

            if ( err )
            {
                fprintf( stderr, "Error! Unable to create thread: %d\n", i );
                exit( EXIT_FAILURE );
            }
        }

        // ожидаем пока потоки закончат выполнение
        if ( threads )
            for ( unsigned i = 0; i < number_of_processors; i++ )
                pthread_join( threads[i], NULL );

        // вычисление Пи, поиск Min Max и рассчёт eps
        double min_pi = DBL_MAX,
               max_pi = DBL_MIN;

        for ( int i = 0; i < number_of_counters; i++ )
        {
            pi = 4.0 * ( double )pi_points_arr[i].good_points / ( double )pi_points_arr[i].all_points;

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
        for ( unsigned i = 0; i < number_of_processors; i++ )
            thread_args[i].how_much_points_to_gen = start;
    }

    return pi;
    #endif
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// реализация версии OpenCL

const unsigned int MAX_SOURCE_SIZE = 0xFFFFFF;

double get_pi_opencl( long number_of_counters,
                      uint32_t start,
                      uint32_t multiplier,
                      double eps,
                      bool use_xs1024 )
{
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;

    fp = fopen( "kernel_boost.cl", "r" );

    if ( !fp )
    {
        fprintf( stderr, "Failed to load OpenCL kernel\n" );
        exit( EXIT_FAILURE );
    }

    source_str = ( char * ) malloc( MAX_SOURCE_SIZE );
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp );
    fclose( fp );

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs( 1, &platform_id, &ret_num_platforms );

    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices );

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret );

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue( context, device_id, 0, &ret );

    size_t local_item_size = 64;

    struct PIPoints *pi_points_arr = ( struct PIPoints * ) malloc( number_of_counters * sizeof( struct PIPoints ) );
    memset( pi_points_arr, 0, number_of_counters * sizeof( struct PIPoints ) );

    unsigned long points_size;

    double *randoms;
    int *points;

    double pi = -1;

    while ( 1 )
    {
        points_size = start * number_of_counters;

        randoms = ( double * ) malloc( points_size * sizeof( double ) );
        points = ( int * ) calloc( points_size, sizeof( int ) );

        // разрадать по сиду каждому kernel
        for ( unsigned i = 0; i < points_size; i++ )
        {
            *( randoms + i ) =
                ( use_xs1024 )
                ? next_xs1024( 0 ) / ( double )RANDOM_MAX
                : next_xs64( 0 ) / ( double )RANDOM_MAX;
        }

        // обработка с OpenCL
        // Create memory buffers on the device for each vector
        cl_mem randoms_mem_obj  = clCreateBuffer( context, CL_MEM_READ_ONLY, points_size * sizeof( double ), NULL, &ret );
        cl_mem points_mem_obj  = clCreateBuffer( context, CL_MEM_WRITE_ONLY, points_size * sizeof( int ), NULL, &ret );

        // Copy the lists @points and @randoms to their respective memory buffers
        ret = clEnqueueWriteBuffer( command_queue, randoms_mem_obj, CL_TRUE, 0, points_size * sizeof( double ), randoms, 0,
                                    NULL, NULL );
        ret = clEnqueueWriteBuffer( command_queue, points_mem_obj, CL_TRUE, 0, points_size * sizeof( int ), points, 0, NULL,
                                    NULL );

        // Create a program from the kernel source
        cl_program program = clCreateProgramWithSource( context, 1, ( const char ** ) &source_str,
                                                        ( const size_t * ) &source_size, &ret );

        // Build the program
        ret = clBuildProgram( program, 1, &device_id, NULL, NULL, NULL );

        // Create the OpenCL kernel
        cl_kernel kernel = clCreateKernel( program, "boost", &ret );

        // Set the arguments of the kernel
        ret = clSetKernelArg( kernel, 0, sizeof( cl_mem ), ( void * ) &randoms_mem_obj );
        ret = clSetKernelArg( kernel, 1, sizeof( cl_mem ), ( void * ) &points_mem_obj );

        // Execute the OpenCL kernel on the list
        size_t global_item_size = points_size;

        ret = clEnqueueNDRangeKernel( command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL );

        // Read the memory buffer @points on the device to the local variable @points
        ret = clEnqueueReadBuffer( command_queue, points_mem_obj, CL_TRUE, 0, points_size * sizeof( int ), points, 0, NULL,
                                   NULL );

        // показать points
        //        for (int i = 0; i < points_size; i++)
        //            printf("points[%d]: %d\n", i, points[i]);

        // суммирование точек в pi_points_arr и поиск min max PI
        double min_pi = DBL_MAX,
               max_pi = DBL_MIN,
               e;

        for ( long i = 0; i < number_of_counters; i++ )
        {
            pi_points_arr[i].all_points += start;

            for ( unsigned j = i; j < points_size; j += number_of_counters )
            {
                if ( points[j] > 1 )
                    points[j] = 1;

                pi_points_arr[i].good_points += ( unsigned long ) points[j];
            }

            pi = 4.0 * pi_points_arr[i].good_points / ( double ) pi_points_arr[i].all_points;

            if ( pi < min_pi )
                min_pi = pi;

            if ( pi > max_pi )
                max_pi = pi;
        }

        //        printf("pi: %f\n",
        //                "min_pi: %f\n"
        //                "max_pi: %f\n", pi, min_pi, max_pi);

        e = max_pi - min_pi;
        //        printf("e: %f\n", e);

        if ( e < eps )
            break;

        start *= multiplier;

        // Clean up
        ret = clFlush( command_queue );
        ret = clFinish( command_queue );

        ret = clReleaseKernel( kernel );
        ret = clReleaseProgram( program );

        ret = clReleaseMemObject( randoms_mem_obj );
        ret = clReleaseMemObject( points_mem_obj );
    }

    ret = clReleaseCommandQueue( command_queue );
    ret = clReleaseContext( context );

    free( randoms );
    free( points );

    return pi;
}