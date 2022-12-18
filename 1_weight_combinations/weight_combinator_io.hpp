/**
 * @file weight_combinator_io.hpp
 * @author Vladimir Nikulin (mail.jorey@gmail.com)
 * @brief Модуль с функционалом ввода/вывода для класса WeightCombinator
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "weight_combinator.hpp"

class WeightCombinator;

/**
 * @brief Перегрузка оператора вывода в стандартный поток комбинаций гирь
 *
 * @param out Объект потока
 * @param data Массив с комбинациями гирь
 * @return std::ostream&
 */
std::ostream &operator<< ( std::ostream &out, WeightCombinator::Combinations const &data );
//std::ostream& operator>> (std::ostream& out, WeightCombinator::Combinations const& data);