#pragma once

#include "pch.hpp"

class RandomGenerator_SampleAbstract
{
public:
    virtual std::vector<double> get_random_vector(unsigned long total_nums, double range_start, double range_end) = 0;
    virtual void print_sample_to_csv(unsigned long total_nums, double range_start, double range_end) = 0;
    
    const virtual std::string& whoami() const = 0;
};
