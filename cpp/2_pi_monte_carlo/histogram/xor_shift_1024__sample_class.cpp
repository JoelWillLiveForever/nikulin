#include "xor_shift_1024__sample_class.hpp"

std::vector<double> XORShift1024_Sample::get_random_vector(unsigned long total_nums, double range_start, double range_end)
{
    XORShift1024_Generator gen( time(NULL) );
    std::vector<double> sample;

    double range = range_end - range_start;

    while (total_nums-- > 0)
    {
        unsigned long long random = gen.next();
        double random_in_range = static_cast<double>(random) / ULLONG_MAX * range + range_start;

        sample.push_back(random_in_range);
    }

    return sample;
}

void XORShift1024_Sample::print_sample_to_csv(unsigned long total_nums, double range_start, double range_end)
{
    std::vector<double> sample = get_random_vector(total_nums, range_start, range_end);

    std::ofstream outfile("xor_shift_1024__sample.csv");
    
    outfile << "randoms" << '\n';    
    while (total_nums-- > 0)
        outfile << sample[total_nums] << '\n';

    outfile.close();
}
