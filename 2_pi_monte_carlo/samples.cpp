#include "samples.hpp"

std::vector<double> MT19937_Sample::get_random_vector(unsigned long total_nums)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    std::vector<double> sample;

    while (total_nums-- > 0)
        sample.push_back( dist(gen) );

    return sample;
}

void MT19937_Sample::print_sample_to_csv(unsigned long total_nums)
{
    std::vector<double> sample = get_random_vector(total_nums);
    std::ofstream outfile( whoami() + ".csv" );
    
    outfile << "randoms" << '\n';
    while (total_nums-- > 0)
        outfile << sample[total_nums] << '\n';

    outfile.close();
}

std::vector<double> XORShift64_Sample::get_random_vector(unsigned long total_nums)
{
    std::vector<double> sample;
    
    while (total_nums-- > 0)
    {
        double random = next_xs64(0) / static_cast<double>(RANDOM_MAX);
        sample.push_back(random);
    }

    return sample;
}

void XORShift64_Sample::print_sample_to_csv(unsigned long total_nums)
{
    std::vector<double> sample = get_random_vector(total_nums);
    std::ofstream outfile( whoami() + ".csv" );
    
    outfile << "randoms" << '\n';    
    while (total_nums-- > 0)
        outfile << sample[total_nums] << '\n';

    outfile.close();
}

std::vector<double> XORShift1024_Sample::get_random_vector(unsigned long total_nums)
{
    std::vector<double> sample;

    while (total_nums-- > 0)
    {
        double random = next_xs1024(0) / static_cast<double>(RANDOM_MAX);
        sample.push_back(random);
    }

    return sample;
}

void XORShift1024_Sample::print_sample_to_csv(unsigned long total_nums)
{
    std::vector<double> sample = get_random_vector(total_nums);
    std::ofstream outfile( whoami() + ".csv" );
    
    outfile << "randoms" << '\n';    
    while (total_nums-- > 0)
        outfile << sample[total_nums] << '\n';

    outfile.close();
}

std::vector<double> CSTDLibRand_Sample::get_random_vector(unsigned long total_nums)
{
    ::srand( (unsigned int)::time(nullptr) );
    std::vector<double> sample;

    while (total_nums-- > 0)
        sample.push_back( (double)rand() / (double)RAND_MAX );

    return sample;
}

void CSTDLibRand_Sample::print_sample_to_csv(unsigned long total_nums)
{
    std::vector<double> sample = get_random_vector(total_nums);
    std::ofstream outfile( whoami() + ".csv" );
    
    outfile << "randoms" << '\n';    
    while (total_nums-- > 0)
        outfile << sample[total_nums] << '\n';

    outfile.close();
}
