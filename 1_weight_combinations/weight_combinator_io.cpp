#include "weight_combinator.hpp"
#include "weight_combinator_io.hpp"

std::ostream& operator<< (std::ostream& out, WeightCombinator::Combinations const& data)
{
    bool first_line = true;

    // вывод в стандартный поток
    for (auto combination : data)
    {
        if (!first_line)
            out << '\n';
        else
            first_line = false;

        for (auto el : combination)
            out << el << ' ';
    }

    return out;
}