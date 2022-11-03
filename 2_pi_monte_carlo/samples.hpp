#pragma once

class RandomGenerator_SampleAbstract
{
public:
    virtual std::vector<double> get_random_vector(unsigned long total_nums) = 0;
    virtual void print_sample_to_csv(unsigned long total_nums) = 0;
    
    const virtual std::string& whoami() const = 0;
};

class MT19937_Sample : public RandomGenerator_SampleAbstract
{
public:
    std::vector<double> get_random_vector(unsigned long total_nums);
    void print_sample_to_csv(unsigned long total_nums = 1000);

    const std::string& whoami() const
    {
        static const std::string result{"mt19937"};
        return result;
    }
};

class XORShift64_Sample : public RandomGenerator_SampleAbstract
{
public:
    std::vector<double> get_random_vector(unsigned long total_nums);
    void print_sample_to_csv(unsigned long total_nums = 1000);


    const std::string& whoami() const
    {
        static const std::string result{"xs64"};
        return result;
    }
};

class XORShift1024_Sample : public RandomGenerator_SampleAbstract
{
public:
    std::vector<double> get_random_vector(unsigned long total_nums);
    void print_sample_to_csv(unsigned long total_nums = 1000);

    const std::string& whoami() const 
    {
        static const std::string result{"xs1024"};
        return result;
    }
};

class CSTDLibRand_Sample : public RandomGenerator_SampleAbstract
{
    std::vector<double> get_random_vector(unsigned long total_nums);
    void print_sample_to_csv(unsigned long total_nums = 1000);

    const std::string& whoami() const 
    {
        static const std::string result{"rand"};
        return result;
    }
};
