#pragma once

#include "stdafx.hpp"
#include "xor_shift_64__generator_class.hpp"

class XORShift1024_Generator
{
private:
    unsigned long long seed_;               // начало последовательности
    std::vector<unsigned long long> S;      // массив из 16 беззнаковых 64-битных целых чисел
    unsigned int i;

public:
    XORShift1024_Generator(unsigned long long seed):
        seed_{seed}, i{0}
    {
        XORShift64_Generator gen(seed_);

        while (i++ < 16)
            S.push_back( gen.next() );
        i = 0;
    }

    void set_seed(unsigned long long seed) 
    { 
        seed_ = seed; 

        XORShift64_Generator gen(seed_);

        i = 0;
        while (i++ < 16)
            S[i] = gen.next();
        i = 0;
    }
    unsigned long long get_seed() { return seed_; }

    unsigned long long next();
};
