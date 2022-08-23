#pragma once

class XORShift64_Generator
{
private:
    unsigned long long seed_;       // начало последовательности
    unsigned long long x;           // последнее сгенерированное число в последовательности

public:
    XORShift64_Generator(unsigned long long seed):
        seed_{seed}, x{seed}
    { }

    void set_seed(unsigned long long seed) { seed_ = seed; }
    unsigned long long get_seed() { return seed_; }

    unsigned long long next();
};
