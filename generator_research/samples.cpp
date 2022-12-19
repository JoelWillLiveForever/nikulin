#include "samples.hpp"

std::vector<double> SampleMT19937::get_random_vector()
{
    std::vector<double> sample;

    unsigned long long count = 0;
    while (count < _sample_size)
    {
        sample.push_back(_dist(_gen));
        count++;
    }

    return sample;
}

void SampleMT19937::print_sample_to_csv()
{
    std::vector<double> sample = get_random_vector();
    std::ofstream outfile( whoami() + ".csv" );

    outfile << "randoms" << '\n';

    unsigned long long count = 0;
    while (count < _sample_size)
    {
        outfile << sample[count] << '\n';
        count++;
    }

    outfile.close();
}

std::vector<double> SampleXS64::get_random_vector()
{
    std::vector<double> sample;

    unsigned long long count = 0;
    if ( _use_classic )
    {
        while ( count < _sample_size )
        {
            uint64_t rnd = next_xs64( &_rctx );
            double random = rnd / static_cast<double>( XS64_MAX ); // 0..1

            sample.push_back( random );
            count++;
        }
    }
    else
    {
        while ( count < _sample_size )
        {
            next_xs64( &_rctx );
            double random = convert_to_double_64( &_rctx );

            sample.push_back( random );
            count++;
        }
    }

    return sample;
}

void SampleXS64::print_sample_to_csv()
{
    std::vector<double> sample = get_random_vector();
    std::ofstream outfile( whoami() + ".csv" );

    outfile << "randoms" << '\n';

    unsigned long long count = 0;
    while (count < _sample_size)
    {
        outfile << sample[count] << '\n';
        count++;
    }

    outfile.close();
}

std::vector<double> SampleXS1024::get_random_vector()
{
    std::vector<double> sample;

    unsigned long long count = 0;
    if ( _use_classic )
    {
        while ( count < _sample_size )
        {
            uint64_t rnd = next_xs1024( &_rctx );
            double random = rnd / static_cast<double>( XS1024_MAX ); // 0..1

            sample.push_back( random );
            count++;
        }
    }
    else
    {
        while ( count < _sample_size )
        {
            next_xs1024( &_rctx );
            double random = convert_to_double_xs1024( &_rctx );

            sample.push_back( random );
            count++;
        }
    }

    return sample;
}

void SampleXS1024::print_sample_to_csv()
{
    std::vector<double> sample = get_random_vector();
    std::ofstream outfile( whoami() + ".csv" );

    outfile << "randoms" << '\n';

    unsigned long long count = 0;
    while (count < _sample_size)
    {
        outfile << sample[count] << '\n';
        count++;
    }

    outfile.close();
}

std::vector<double> SampleRand16::get_random_vector()
{
    std::vector<double> sample;

    unsigned long long count = 0;
    if ( _use_classic )
    {
        while ( count < _sample_size )
        {
            // генерируем 64 битное число
            uint64_t rnd = 0;

            // 1
            rnd |= next_rand16(&_rctx);

            // 2
            rnd <<= 16;
            rnd |= next_rand16(&_rctx);

            // 3
            rnd <<= 16;
            rnd |= next_rand16(&_rctx);

            // 4
            rnd <<= 16;
            rnd |= next_rand16(&_rctx);

            double random = rnd / static_cast<double>( RAND16_MAX );

            sample.push_back( random );
            count++;
        }
    }
    else
    {
        while ( count < _sample_size )
        {
            next_rand16( &_rctx );
            double random = convert_to_double_rand16( &_rctx ); // метод догенерирует ещё 3 числа rand16, чтобы создать double

            sample.push_back( random );
            count++;
        }
    }

    return sample;
}

void SampleRand16::print_sample_to_csv()
{
    std::vector<double> sample = get_random_vector();
    std::ofstream outfile( whoami() + ".csv" );

    outfile << "randoms" << '\n';

    unsigned long long count = 0;
    while (count < _sample_size)
    {
        outfile << sample[count] << '\n';
        count++;
    }

    outfile.close();
}

std::vector<double> SampleRand32::get_random_vector()
{
    std::vector<double> sample;

    unsigned long long count = 0;
    if (_use_classic)
    {
        while (count < _sample_size)
        {
            // генерируем 64 битное число
            uint64_t rnd = 0;

            // 1
            rnd |= next_rand32(&_rctx);

            // 2
            rnd <<= 32;
            rnd |= next_rand32(&_rctx);

            double random = rnd / static_cast<double>(RAND32_MAX);

            sample.push_back(random);
            count++;
        }
    }
    else
    {
        while (count < _sample_size)
        {
            next_rand32(&_rctx);
            double random = convert_to_double_rand32(&_rctx); // метод догенерирует ещё 1 число rand32, чтобы создать double

            sample.push_back(random);
            count++;
        }
    }

    return sample;
}

void SampleRand32::print_sample_to_csv()
{
    std::vector<double> sample = get_random_vector();
    std::ofstream outfile(whoami() + ".csv");

    outfile << "randoms" << '\n';

    unsigned long long count = 0;
    while (count < _sample_size)
    {
        outfile << sample[count] << '\n';
        count++;
    }

    outfile.close();
}
