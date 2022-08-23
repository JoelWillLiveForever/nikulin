#include "mt19937__sample_class.hpp"

std::vector<double> MT19937_Sample::get_random_vector(unsigned long total_nums, double range_start, double range_end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(range_start, range_end);

    std::vector<double> sample;

    while (total_nums-- > 0)
        sample.push_back(dist(gen));

    return sample;
}

void MT19937_Sample::print_sample_to_csv(unsigned long total_nums, double range_start, double range_end)
{
    std::vector<double> sample = get_random_vector(total_nums, range_start, range_end);

    std::ofstream outfile("mt19937__sample.csv");
        
    outfile << "randoms" << '\n';
    while (total_nums-- > 0)
        outfile << sample[total_nums] << '\n';

    outfile.close();
}
