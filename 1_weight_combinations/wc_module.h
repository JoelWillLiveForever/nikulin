/**
 * @file wc_module.h
 * @author Vladimir Nikulin (mail.jorey@gmail.com)
 * @brief Заголовочный файл для модуля wc_module.c
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __WC_MODULE_H__ // Include Guard
#define __WC_MODULE_H__

#include "../random/src/xor_shift.h"

/// @brief Перечисление поддерживаемых алгоритмов решения задачи
enum Solution
{
    RECURSIVE,
    BITS
};

/// @brief Максимальный размер номенлктары гирь, если выбран алгоритм BITS
static const char _allowed_bits = sizeof( unsigned int ) * 8;

// TODO: расставить const
/**
 * @brief Методя для рассчёта количества всех возможных вариантов использования гирь, из которых получается заданный вес
 *
 * @param solution Выбор алгоритма решения задачи
 * @param nomenclature Номенклатура весов
 * @param nomenclature_size Размер номенклатуры
 * @param target Целевой вес. Как раз для него и ищем комбинации
 * @param out_combinations Итоговые комбинации гирь
 * @return int Размер массива out_combinations (по совместительству - количество комбинаций для данного целевого веса)
 */
int get_number_of_combinations( enum Solution *solution, unsigned int *nomenclature, unsigned int *nomenclature_size,
                                unsigned int *target, unsigned int ***out_combinations );

#endif