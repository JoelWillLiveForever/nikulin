#include "counters.h"

typedef struct
{
    uint64_t good_points;
    uint64_t all_points;
} PIPoints;

void generate_points( PIPoints *pi_points_array,
                      uint32_t i,
                      uint32_t how_much_to_gen,
                      GeneratorType generator_type )
{
    if ( !pi_points_array ) // проверка на нулевой указатель
    {
        fprintf( stderr, "Bad pointer for \"pi_points_array\" in module \'counters.c\'\n" );
        return;
    }

    pi_points_array[i].all_points += how_much_to_gen;

    static bool isInit = true;  // инициализируем генераторы только один раз

    static RandomContext16 rctx16;
    static RandomContext32 rctx32;
    static RandomContext64 rctx64;
    static RandomContext1024 rctx1024;

    if ( isInit )
    {
        InitRandomContext16( &rctx16 );
        InitRandomContext32( &rctx32 );
        InitRandomContext64( &rctx64 );
        InitRandomContext1024( &rctx1024 );

        isInit = false;
    }

    unsigned long random_buffer_size = 2 * how_much_to_gen;
    double *random_buffer = ( double * )malloc( random_buffer_size * sizeof( double ) );

    int ret = 0;

    switch ( generator_type )
    {
        case XOR_SHIFT_16:
            ret = fill_buffer_xs16( &rctx16, random_buffer, random_buffer_size );
            break;

        case XOR_SHIFT_32:
            ret = fill_buffer_xs32( &rctx32, random_buffer, random_buffer_size );
            break;

        case XOR_SHIFT_64:
            ret = fill_buffer_xs64( &rctx64, random_buffer, random_buffer_size );
            break;

        case XOR_SHIFT_1024:
            ret = fill_buffer_xs1024( &rctx1024, random_buffer, random_buffer_size );
            break;

        case RAND16:
            ret = fill_buffer_rand16( &rctx16, random_buffer, random_buffer_size );
            break;

        case RAND32:
            ret = fill_buffer_rand32( &rctx32, random_buffer, random_buffer_size );
            break;

        case RAND64:
            ret = fill_buffer_rand64( &rctx64, random_buffer, random_buffer_size );
            break;

        default:
            fprintf( stderr, "You didn't specify a generator type" );
            break;
    }

    if ( ret == -1 )
    {
        fprintf( stderr, "Cannot fill *random_buffer" );
        return;
    }

    uint8_t len = 0;
    double x = 0, y = 0;

    for ( double *ptr = random_buffer, *end = random_buffer + random_buffer_size; ptr != end; ptr += 2 )
    {
        x = *ptr;
        y = *( ptr + 1 );

        len = !( uint8_t )( x * x + y * y );
        pi_points_array[i].good_points += len;
    }

    free( random_buffer );
}

double get_pi_single_thread( uint32_t number_of_counters,
                             uint32_t start,
                             uint32_t multiplier,
                             double precision,
                             GeneratorType generator_type )
{
    PIPoints *pi_points_array = ( PIPoints * )calloc( number_of_counters, sizeof( PIPoints ) );

    if ( !pi_points_array )
    {
        fprintf( stderr, "Cannot create *pi_points_array with calloc" );
        return -1;
    }

    unsigned int i;
    double min_pi, max_pi, pi;

    while ( 1 )
    {
        min_pi = DBL_MAX;
        max_pi = DBL_MIN;
        pi = -1;

        for ( i = 0; i < number_of_counters; i++ )
        {
            generate_points( pi_points_array, i, start, generator_type );
            pi = 4.0 * ( double )pi_points_array[i].good_points / ( double )pi_points_array[i].all_points;

            if ( min_pi > pi )
                min_pi = pi;

            if ( max_pi < pi )
                max_pi = pi;
        }

        double e = max_pi - min_pi;

        if ( e < precision )
            break;

        start *= multiplier;
    }

    return pi;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// реализация версии multithread
///////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    PIPoints *pi_points_array;                  // каждый поток считает свои Пи

    unsigned int
    *pi_points_array_indexes;      // индекс чисел Пи, с которыми работает данный поток
    unsigned int
    pi_points_array_indexes_size;  // сколько Пи нужно рассчитать конкретно этому потоку

    unsigned int how_much_to_gen;

    GeneratorType generator_type;
} ThreadArgs;

//pthread_mutex_t locker;

void *generate_points_in_thread( void *thread_args )
{
    ThreadArgs *args = ( ThreadArgs * )thread_args;

    if ( !args )
        return NULL;

    RandomContext16 rctx16;
    RandomContext32 rctx32;
    RandomContext64 rctx64;
    RandomContext1024 rctx1024;

    InitRandomContext16( &rctx16 );
    InitRandomContext32( &rctx32 );
    InitRandomContext64( &rctx64 );
    InitRandomContext1024( &rctx1024 );

    unsigned int how_much_to_gen = args->how_much_to_gen;

    // TODO: Ограничить потребление памяти программой
    //// разрешаю забить памяти на 4 ГБ
    //unsigned long max_size = 4 * 1024 * 1024;   // максимально разрешённое число байт для буфера
    //unsigned long random_buffer_full_size = 2 * how_much_to_gen;    // полный размер в байтах, требуемый буферу

    unsigned long random_buffer_size = 2 * how_much_to_gen;
    double *random_buffer = ( double * )malloc( random_buffer_size * sizeof( double ) );

    for ( unsigned int *index = args->pi_points_array_indexes,
            *last_index = args->pi_points_array_indexes + args->pi_points_array_indexes_size; index != last_index; index++ )
    {
        args->pi_points_array[*index].all_points += how_much_to_gen;

        int ret = 0;

        switch ( args->generator_type )
        {
            case XOR_SHIFT_16:
                ret = fill_buffer_xs16( &rctx16, random_buffer, random_buffer_size );
                break;

            case XOR_SHIFT_32:
                ret = fill_buffer_xs32( &rctx32, random_buffer, random_buffer_size );
                break;

            case XOR_SHIFT_64:
                ret = fill_buffer_xs64( &rctx64, random_buffer, random_buffer_size );
                break;

            case XOR_SHIFT_1024:
                ret = fill_buffer_xs1024( &rctx1024, random_buffer, random_buffer_size );
                break;

            case RAND16:
                ret = fill_buffer_rand16( &rctx16, random_buffer, random_buffer_size );
                break;

            case RAND32:
                ret = fill_buffer_rand32( &rctx32, random_buffer, random_buffer_size );
                break;

            case RAND64:
                ret = fill_buffer_rand64( &rctx64, random_buffer, random_buffer_size );
                break;

            default:
                fprintf( stderr, "You didn't specify a generator type" );
                break;
        }

        if ( ret == -1 )
        {
            fprintf( stderr, "Cannot fill *random_buffer" );
            return NULL;
        }

        uint8_t len = 0;
        double x = 0, y = 0;

        for ( double *ptr = random_buffer, *end = random_buffer + random_buffer_size; ptr != end; ptr += 2 )
        {
            x = *ptr;
            y = *( ptr + 1 );

            len = !( uint8_t )( x * x + y * y );
            args->pi_points_array[*index].good_points += len;
        }
    }

    free( random_buffer );
    return NULL;
}

double get_pi_multithread( uint32_t number_of_counters,
                           uint32_t start,
                           uint32_t multiplier,
                           double precision,
                           long number_of_processors,
                           GeneratorType generator_type )
{
    PIPoints *pi_points_array = ( PIPoints * )calloc( number_of_counters, sizeof( PIPoints ) );

    if ( !pi_points_array )
    {
        fprintf( stderr, "Cannot create *pi_points_array with calloc" );
        return -1;
    }

    ThreadArgs *thread_args = ( ThreadArgs * )calloc( number_of_processors, sizeof( ThreadArgs ) );

    if ( !thread_args )
    {
        fprintf( stderr, "Cannot create *thread_args with calloc" );
        return -1;
    }

    // разбить pi_points_array на части и распределить эти части между потоками
    for ( long thread_index = 0; thread_index < number_of_processors; thread_index++ )
    {
        thread_args[thread_index].pi_points_array =
            pi_points_array;    // каждый поток получит копию указателя на весь массив pi_points_array
        thread_args[thread_index].generator_type = generator_type;
        thread_args[thread_index].how_much_to_gen =
            start;              // установить кол-во точек для генерации

        unsigned int pi_points_array_indexes_size =
            0;                  // количество чисел Пи, которые будет генерировать данный поток

        for ( unsigned int pi_points_array_index = thread_index; pi_points_array_index < number_of_counters;
                pi_points_array_index += number_of_processors )
        {
            if ( thread_args[thread_index].pi_points_array_indexes )
            {
                // расширяем динамический массив
                unsigned int *temp = ( unsigned int * )realloc( thread_args[thread_index].pi_points_array_indexes,
                                                                ( ++pi_points_array_indexes_size ) * sizeof( unsigned int ) );

                if ( !temp )
                {
                    fprintf( stderr, "Cannot resize *thread_args[%ld].pi_points_array_indexes with realloc", thread_index );
                    return -1;
                }

                thread_args[thread_index].pi_points_array_indexes = temp;
            }
            else
            {
                unsigned int *temp = ( unsigned int * )calloc( ++pi_points_array_indexes_size, sizeof( unsigned int ) );

                if ( !temp )
                {
                    fprintf( stderr, "Cannot create *thread_args[%ld].pi_points_array_indexes with calloc", thread_index );
                    return -1;
                }

                thread_args[thread_index].pi_points_array_indexes = temp;
            }

            unsigned int *last_element = &thread_args[thread_index].pi_points_array_indexes[pi_points_array_indexes_size - 1];
            *last_element = pi_points_array_index;
        }

        thread_args[thread_index].pi_points_array_indexes_size = pi_points_array_indexes_size;
    }

    // создаём массив потоков
    pthread_t *threads = malloc( number_of_processors * sizeof( pthread_t ) );

    if ( !threads )
    {
        fprintf( stderr, "Cannot create *threads with calloc" );
        return -1;
    }

    double pi = -1;

    while ( 1 ) // находимся в цикле, пока Пи не достигнем заданной точности
    {
        // запускаем потоки на выполнение
        for ( long i = 0; i < number_of_processors; i++ )
        {
            int err = pthread_create( &threads[i], NULL, generate_points_in_thread, ( void * )&thread_args[i] );

            if ( err )
            {
                fprintf( stderr, "Error! Unable to create thread: %ld\n", i );
                return -1;
            }
        }

        // ожидаем пока все потоки закончат выполнение
        for ( long i = 0; i < number_of_processors; i++ )
            pthread_join( threads[i], NULL );

        // вычисление Пи, поиск Min Max и рассчёт precision
        double min_pi = DBL_MAX,
               max_pi = DBL_MIN;

        for ( unsigned int i = 0; i < number_of_counters; i++ )
        {
            uint64_t good_points = pi_points_array[i].good_points;
            uint64_t all_points = pi_points_array[i].all_points;

            pi = 4.0 * good_points / ( double )all_points;

            if ( min_pi > pi )
                min_pi = pi;

            if ( max_pi < pi )
                max_pi = pi;
        }

        double my_precision = max_pi - min_pi;

        if ( my_precision < precision )
            break;

        start *= multiplier;

        // обновляем how_much_to_gen у всех потоков
        for ( long i = 0; i < number_of_processors; i++ )
            thread_args[i].how_much_to_gen = start;
    }

    return pi;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// реализация версии OpenCL
///////////////////////////////////////////////////////////////////////////////////////////////

extern const char *kernel_source;
double get_pi_opencl( uint32_t number_of_counters,
                      uint64_t start,
                      uint32_t multiplier,
                      double precision,
                      GeneratorType generator_type )
{
    double pi = 0;

    RandomContext64 rctx64;
    RandomContext1024 rctx1024;

    InitRandomContext64( &rctx64 );
    InitRandomContext1024( &rctx1024 );

    size_t kernel_code_size = strlen( kernel_source );
    cl_int ret;

    // Get the number of platforms
    cl_uint num_platforms;
    ret = clGetPlatformIDs( 0, NULL, &num_platforms );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot getting platform IDs: %d\n", ret );
        return -1;
    }

    if ( num_platforms == 0 )
    {
        fprintf( stdout, "No available OpenCL platforms\n" );
        return -2;
    }

    cl_platform_id *platforms = ( cl_platform_id * )malloc( num_platforms * sizeof( cl_platform_id ) );

    if ( !platforms )
    {
        fprintf( stderr, "Cannot allocating memory for platform IDs\n" );
        return -1;
    }

    ret = clGetPlatformIDs( num_platforms, platforms, NULL );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot getting platform IDs\n" );
        return -1;
    }

    cl_platform_id platform = platforms[0];
    free( platforms );

    cl_uint num_devices = 0;
    ret = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot getting GPU devices IDs: %d\n", ret );
        return -1;
    }

    cl_device_id *devices;

    if ( num_devices == 0 )
    {
        fprintf( stdout, "No GPU device available\n" );
        fprintf( stdout, "Choose CPU as default device\n" );

        ret = clGetDeviceIDs( platform, CL_DEVICE_TYPE_CPU, 0, NULL, &num_devices );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot getting CPU devices IDs: %d\n", ret );
            return -1;
        }

        if ( num_devices == 0 )
        {
            fprintf( stdout, "No CPU device available\n" );
            return -2;
        }

        devices = ( cl_device_id * )malloc( num_devices * sizeof( cl_device_id ) );

        if ( !devices )
        {
            fprintf( stderr, "Cannot allocating memory for devices IDs\n" );
            return -1;
        }

        ret = clGetDeviceIDs( platform, CL_DEVICE_TYPE_CPU, num_devices, devices, NULL );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot getting CPU devices IDs: %d\n", ret );
            return -1;
        }
    }
    else
    {
        devices = ( cl_device_id * )malloc( num_devices * sizeof( cl_device_id ) );

        if ( !devices )
        {
            fprintf( stderr, "Cannot allocating memory for devices IDs\n" );
            return -1;
        }

        ret = clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU, num_devices, devices, NULL );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot getting GPU devices IDs: %d\n", ret );
            return -1;
        }
    }

    cl_device_id device = devices[0];
    free( devices );

    // request max memory size for cl_mem_obj for this device
    cl_ulong max_memory_allocation_size;
    ret = clGetDeviceInfo( device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof( cl_ulong ), &max_memory_allocation_size, NULL );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot get CL_DEVICE_MAX_MEM_ALLOC_SIZE: %d\n", ret );
        return -1;
    }

    // request max available compute units for this device
    size_t max_work_group_size;
    ret = clGetDeviceInfo( device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof( size_t ), &max_work_group_size, NULL );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot get CL_DEVICE_MAX_WORK_GROUP_SIZE: %d\n", ret );
        return -1;
    }

    // display the received values
    //fprintf(stdout, "max_memory_allocation_size: %llu\nmax_work_group_size: %llu\n\n", max_memory_allocation_size, max_work_group_size);

    cl_context context = clCreateContext( NULL, 1, &device, NULL, NULL, &ret );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot create cl_context: %d\n", ret );
        return -1;
    }

    cl_command_queue command_queue = clCreateCommandQueueWithProperties( context, device, NULL, &ret );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot create command_queue: %d\n", ret );
        return -1;
    }

    cl_program program = clCreateProgramWithSource( context, 1, ( const char ** )&kernel_source,
                                                    ( const size_t * )&kernel_code_size, &ret );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot create cl_program: %d\n", ret );
        return -1;
    }

    ret = clBuildProgram( program, 1, &device, NULL, NULL, NULL );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot build cl_program: %d\n", ret );

        size_t log_size;
        clGetProgramBuildInfo( program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size );

        char *log = ( char * )malloc( log_size + 1 );

        if ( !log )
        {
            fprintf( stderr, "Cannot allocate memory for *log variable\n" );
            return -1;
        }

        clGetProgramBuildInfo( program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL );

        log[log_size] = '\0';
        fprintf( stderr, "Build log:\n%s\n", log );

        free( log );
        return -1;
    }

    // seeds size and number of points to generate
    uint64_t seeds_size = number_of_counters * start;

    // Create mem objects
    cl_mem mem_pi_points_array = clCreateBuffer( context, CL_MEM_READ_WRITE, number_of_counters * sizeof( PIPoints ), NULL,
                                                 &ret );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot create mem_pi_points_array: %d\n", ret );
        return -1;
    }

    cl_mem mem_generator_type = clCreateBuffer( context, CL_MEM_READ_WRITE, sizeof( GeneratorType ), NULL, &ret );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot create mem_generator_type: %d\n", ret );
        return -1;
    }

    cl_mem mem_error_code = clCreateBuffer( context, CL_MEM_READ_WRITE, sizeof( int ), NULL, &ret );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot create mem_error_code: %d\n", ret );
        return -1;
    }

    // Write data to cl_mem objects
    PIPoints *pi_points_array = ( PIPoints * )calloc( number_of_counters, sizeof( PIPoints ) );

    if ( !pi_points_array )
    {
        fprintf( stderr, "Cannot allocate memory for *pi_points_array with calloc\n" );
        return -1;
    }

    ret = clEnqueueWriteBuffer( command_queue, mem_pi_points_array, CL_TRUE, 0, number_of_counters * sizeof( PIPoints ),
                                pi_points_array, 0, NULL, NULL );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot write data to mem_pi_points_array: %d\n", ret );
        return -1;
    }

    uint64_t *seeds = ( uint64_t * )malloc( seeds_size * sizeof( uint64_t ) );

    if ( !seeds )
    {
        fprintf( stderr, "Cannot allocate memory for *seeds with malloc\n" );
        return -1;
    }

    ret = clEnqueueWriteBuffer( command_queue, mem_generator_type, CL_TRUE, 0, sizeof( GeneratorType ), &generator_type, 0,
                                NULL, NULL );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot write data to mem_generator_type: %d\n", ret );
        return -1;
    }

    int opencl_error_code = 0;
    ret = clEnqueueWriteBuffer( command_queue, mem_error_code, CL_TRUE, 0, sizeof( int ), &opencl_error_code, 0, NULL,
                                NULL );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot write data to mem_error_code: %d\n", ret );
        return -1;
    }

    // Generate seeds
    switch ( generator_type )
    {
        case XOR_SHIFT_64:
            for ( uint64_t *ptr = seeds, *end = seeds + seeds_size; ptr != end; ptr++ )
                *ptr = next_xs64( &rctx64 );

            break;

        case XOR_SHIFT_1024:
            for ( uint64_t *ptr = seeds, *end = seeds + seeds_size; ptr != end; ptr++ )
                *ptr = next_xs1024( &rctx1024 );

            break;

        default:
            fprintf( stderr, "OpenCL only support XorShift64 and XorShift1024 generator type\n" );
            return -1;
    }

    uint64_t *pi_points_array_indexes = ( uint64_t * )malloc( seeds_size * sizeof( uint64_t ) );

    if ( !pi_points_array_indexes )
    {
        fprintf( stderr, "Cannot allocate memory for *pi_points_array_indexes with malloc\n" );
        return -1;
    }

    uint64_t index = 0;

    for ( uint64_t *ptr = pi_points_array_indexes, *end = pi_points_array_indexes + seeds_size; ptr != end; ptr++ )
    {
        index = ( end - ptr ) / start;
        *ptr = index;
    }

    bool is_memory_available = true;
    uint64_t new_seeds_size = seeds_size;

    //uint64_t counter = 0;
    while ( 1 )
    {
        if ( is_memory_available && seeds_size < new_seeds_size )
        {
            // нужно сделать realloc *seeds и *pi_points_array_indexes
            uint64_t *temp = ( uint64_t * )realloc( seeds, new_seeds_size * sizeof( uint64_t ) );

            if ( !temp )
            {
                fprintf( stderr, "Cannot allocate memory for *seeds with realloc\n" );
                return -1;
            }

            seeds = temp;

            temp = ( uint64_t * )realloc( pi_points_array_indexes, new_seeds_size * sizeof( uint64_t ) );

            if ( !temp )
            {
                fprintf( stderr, "Cannot allocate memory for *pi_points_array_indexes with realloc\n" );
                return -1;
            }

            pi_points_array_indexes = temp;

            // теперь дополним *seeds новыми сидами
            switch ( generator_type )
            {
                case XOR_SHIFT_64:
                    for ( uint64_t *ptr = seeds + seeds_size, *end = seeds + new_seeds_size; ptr != end; ptr++ )
                        *ptr = next_xs64( &rctx64 );

                    break;

                case XOR_SHIFT_1024:
                    for ( uint64_t *ptr = seeds + seeds_size, *end = seeds + new_seeds_size; ptr != end; ptr++ )
                        *ptr = next_xs1024( &rctx1024 );

                    break;

                default:
                    fprintf( stderr, "OpenCL only support XorShift64 and XorShift1024 generator type\n" );
                    return -1;
            }

            // а pi_points_array_indexes обновим индексы
            for ( uint64_t *ptr = pi_points_array_indexes, *end = pi_points_array_indexes + new_seeds_size; ptr != end; ptr++ )
            {
                index = ( end - ptr ) / start;
                *ptr = index;
            }

            seeds_size = new_seeds_size;
        }

        // Create mem_objects with current seeds_size
        cl_mem mem_seeds = clCreateBuffer( context, CL_MEM_READ_WRITE, seeds_size * sizeof( uint64_t ), NULL, &ret );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot create mem_seeds: %d\n", ret );
            return -1;
        }

        cl_mem mem_pi_points_array_indexes = clCreateBuffer( context, CL_MEM_READ_WRITE, seeds_size * sizeof( uint64_t ), NULL,
                                                             &ret );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot create mem_pi_points_array_indexes: %d\n", ret );
            return -1;
        }

        // Write data to mem_objects
        ret = clEnqueueWriteBuffer( command_queue, mem_error_code, CL_TRUE, 0, sizeof( int ), &opencl_error_code, 0, NULL,
                                    NULL );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot write data to mem_error_code: %d\n", ret );
            return -1;
        }

        if ( opencl_error_code == -1 )  // generator type not supported
        {
            fprintf( stderr, "OpenCL only support XorShift64 and XorShift1024 generator type\n" );
            return -1;
        }

        ret = clEnqueueWriteBuffer( command_queue, mem_seeds, CL_TRUE, 0, seeds_size * sizeof( uint64_t ), seeds, 0, NULL,
                                    NULL );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot write data to mem_seeds: %d\n", ret );
            return -1;
        }

        ret = clEnqueueWriteBuffer( command_queue, mem_pi_points_array_indexes, CL_TRUE, 0, seeds_size * sizeof( uint64_t ),
                                    pi_points_array_indexes, 0, NULL, NULL );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot write data to mem_pi_points_array_indexes: %d\n", ret );
            return -1;
        }

        // Create a kernel
        const char *kernel_name = "boost";
        cl_kernel kernel = clCreateKernel( program, kernel_name, &ret );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot create cl_kernel: %d\n", ret );
            return -1;
        }

        // Set kernel arguments
        ret = clSetKernelArg( kernel, 0, sizeof( cl_mem ), ( void * )&mem_pi_points_array );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot set mem_pi_points_array as argument: %d\n", ret );
            return -1;
        }

        ret = clSetKernelArg( kernel, 1, sizeof( cl_mem ), ( void * )&mem_seeds );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot set mem_seeds as argument: %d\n", ret );
            return -1;
        }

        ret = clSetKernelArg( kernel, 2, sizeof( cl_mem ), ( void * )&mem_pi_points_array_indexes );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot set mem_pi_points_array_indexes as argument: %d\n", ret );
            return -1;
        }

        ret = clSetKernelArg( kernel, 3, sizeof( cl_mem ), ( void * )&mem_generator_type );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot set mem_generator_type as argument: %d\n", ret );
            return -1;
        }

        ret = clSetKernelArg( kernel, 4, sizeof( cl_mem ), ( void * )&mem_error_code );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot set mem_error_code as argument: %d\n", ret );
            return -1;
        }

        // Running the kernel
        ret = clEnqueueNDRangeKernel( command_queue, kernel, 1, NULL, ( const size_t * ) & seeds_size,
                                      ( const size_t * )&max_work_group_size, 0, NULL, NULL );

        // на карте NVidia выдаёт такую ошибку
        if ( ret == CL_INVALID_WORK_GROUP_SIZE )
        {
            //fprintf(stdout, "Cannot use CL_DEVICE_MAX_WORK_GROUP_SIZE: %llu\nTry use CL_KERNEL_WORK_GROUP_SIZE...\n", max_work_group_size);

            size_t kernel_work_group_size;
            ret = clGetKernelWorkGroupInfo( kernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof( size_t ), &kernel_work_group_size,
                                            NULL );

            if ( ret != CL_SUCCESS )
            {
                fprintf( stderr, "Cannot get CL_KERNEL_WORK_GROUP_SIZE: %d\n", ret );
                return -1;
            }

            //fprintf(stdout, "CL_KERNEL_WORK_GROUP_SIZE: %llu\n", kernel_work_group_size);

            // на карте NVidia также может не сработать этот вариант
            ret = clEnqueueNDRangeKernel( command_queue, kernel, 1, NULL, ( const size_t * )&seeds_size,
                                          ( const size_t * )&kernel_work_group_size, 0, NULL, NULL );

            if ( ret != CL_SUCCESS )
            {
                // если последний вариант запуска не сработает, выдать ошибку
                ret = clEnqueueNDRangeKernel( command_queue, kernel, 1, NULL, ( const size_t * )&seeds_size,
                                              NULL, 0, NULL, NULL );

                if ( ret != CL_SUCCESS )
                {
                    fprintf( stderr, "Cannot run kernel: %d\n", ret );
                    return -1;
                }
            }

            // Success
        }
        else if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot run kernel: %d\n", ret );
            return -1;
        }

        // Read the memory buffer
        ret = clEnqueueReadBuffer( command_queue, mem_pi_points_array, CL_TRUE, 0, number_of_counters * sizeof( PIPoints ),
                                   pi_points_array, 0, NULL, NULL );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot read data from mem_pi_points_array: %d\n", ret );
            return -1;
        }

        // Calculate PI numbers and find MIN and MAX PI
        double min_pi = DBL_MAX;
        double max_pi = DBL_MIN;

        for ( PIPoints *ptr = pi_points_array, *end = pi_points_array + number_of_counters; ptr != end; ptr++ )
        {
            //fprintf(stdout, "Index: %llu\n\n", (end - ptr));
            //fprintf(stdout, "good_points: %llu\nall_points: %llu\n\n", ptr->good_points, ptr->all_points);

            pi = 4.0 * ptr->good_points / ( double )ptr->all_points;

            if ( pi > max_pi )
                max_pi = pi;

            if ( pi < min_pi )
                min_pi = pi;
        }

        // Cleanup kernel and mem_objects
        ret = clReleaseKernel( kernel );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot release cl_kernel: %d\n", ret );
            return -1;
        }

        ret = clReleaseMemObject( mem_seeds );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot release mem_seeds: %d\n", ret );
            return -1;
        }

        ret = clReleaseMemObject( mem_pi_points_array_indexes );

        if ( ret != CL_SUCCESS )
        {
            fprintf( stderr, "Cannot mem_pi_points_array_indexes: %d\n", ret );
            return -1;
        }

        // Calculate local precision and check with global precision
        double my_precision = max_pi - min_pi;

        if ( my_precision <= precision )
            break;

        if ( is_memory_available )
        {
            start *= multiplier;
            new_seeds_size = number_of_counters * start;

            if ( new_seeds_size * sizeof( uint64_t ) > max_memory_allocation_size )
            {
                new_seeds_size = seeds_size;
                is_memory_available = false;
            }
        }

        //if (counter % 2 == 0)
        //{
        //    fprintf(stdout, "Current pi: %Lf\n", pi);
        //    counter = 0;
        //}

        //counter++;
    }

    // Other cleanup
    ret = clReleaseProgram( program );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot release cl_program: %d\n", ret );
        return -1;
    }

    ret = clReleaseMemObject( mem_pi_points_array );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot release mem_pi_points_array: %d\n", ret );
        return -1;
    }

    ret = clReleaseMemObject( mem_generator_type );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot release mem_generator_type: %d\n", ret );
        return -1;
    }

    ret = clReleaseMemObject( mem_error_code );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot release mem_error_code: %d\n", ret );
        return -1;
    }

    ret = clReleaseCommandQueue( command_queue );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot release cl_command_queue: %d\n", ret );
        return -1;
    }

    ret = clReleaseContext( context );

    if ( ret != CL_SUCCESS )
    {
        fprintf( stderr, "Cannot release cl_context: %d\n", ret );
        return -1;
    }

    free( pi_points_array );
    free( seeds );
    free( pi_points_array_indexes );

    return pi;
}
