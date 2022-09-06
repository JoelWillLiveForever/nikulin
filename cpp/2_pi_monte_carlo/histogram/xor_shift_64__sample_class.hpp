#pragma once

#include "stdafx.hpp"

#include "random_generator__sample_abstract_class.hpp"
#include "xor_shift_64__generator_class.hpp"

class XORShift64_Sample : public RandomGenerator_SampleAbstract
{
public:
    std::vector<double> get_random_vector(unsigned long total_nums, double range_start, double range_end);
    void print_sample_to_csv(unsigned long total_nums = 1000, double range_start = 0, double range_end = 1);


    const std::string& whoami() const
    {
        static const std::string result{"xor-shift-64"};
        return result;
    }
};
