/**
 * @file weight_combinator_io.cpp
 * @author Vladimir Nikulin (mail.jorey@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "weight_combinator.hpp"
#include "weight_combinator_io.hpp"

/**
 * @brief Вывод WeightCombinator::Combinations в stdout
 *
 * @param out Ссылка на объект потока
 * @param data Ссылка на объект WeightCombinator::Combinations
 * @return std::ostream& Возвращаем ссылку на объект потока
 */
std::ostream &operator<< ( std::ostream &out, WeightCombinator::Combinations const &data )
{
    bool first_line = true;

    // вывод в стандартный поток
    for ( auto combination : data )
    {
        if ( !first_line )
            out << '\n';
        else
            first_line = false;

        for ( auto el : combination )
            out << el << ' ';
    }

    return out;
}