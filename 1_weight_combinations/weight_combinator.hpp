#pragma once

#include "../pch.hpp"

class WeightCombinator
{
public:
    typedef std::vector<unsigned int> Weights;                           // тип для хранения номенклатуры гирь
    typedef std::vector<std::vector<unsigned int>> Combinations;         // тип для хранения комбинаций

private:
    static const char allowed_bits_ = sizeof(unsigned int) * 8;  // максимальное количество гирь, которое можно задать    

public:

    // read-only
    static char get_allowed_bits() { return allowed_bits_; };

    void combine(unsigned int target, 
            WeightCombinator::Combinations &combinations, 
            WeightCombinator::Weights &weights);                // метод поиска комбинаций для заданного веса

    //TODO: try fix it
    //friend inline std::ostream& operator<<(std::ostream& out, const WeightCombinator::Combinations& data);
    //friend inline std::ostream& operator<<(std::ostream& out, const WeightCombinator& obj);
};
