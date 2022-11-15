/**
 * @file wc_module.c
 * @author Vladimir Nikulin (mail.jorey@gmail.com)
 * @brief Реализация функционала для модуля wc_module.h
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../stable.h"  // C precompiled headers

#include "wc_module.h"
#include "../random/src/xor_shift.h"

/**
 * @brief Функция рекурсии, каждый раз вызывает саму себя и отнимает по одной гире из номенклатуры
 * 
 * @param target Целевой вес, уменьшается с каждой итерацией рекурсии
 * @param weight Текущая гиря, удаляется из номенклатуры на предыдущей итерации
 * @param weight_id Id-шник этой гири
 * @param nomenclature Оставшаяся номенклатура с гирями
 * @param weights_ids Оставшиеся id-шники
 * @param nomenclature_size Размер оставшейся номенклатуры
 * @param current_combination Кандидат в комбинацию, тут храняться все выбранные гири
 * @param weights_counter Счётчик для current_combination
 * @param weights_ids_sums Текущая 'накопленная' сумма id-шников, позволяет выявлять уникальные комбинации
 * @param number_of_combinations Счётчик комбинаций
 * @param combinations Найденные комбинации
 * @param max_combinations Максимально возможное количество комбинаций (всегда const)
 * @param original_nomenclature_size Размер оригинальной номенклатуры гирь
 */
void search_combinations_recursive(int target, unsigned int weight, unsigned int weight_id, unsigned int* nomenclature, unsigned int* weights_ids, unsigned int* nomenclature_size, unsigned int* current_combination, int* weights_counter, unsigned int* weights_ids_sums, int* number_of_combinations, unsigned int** combinations, unsigned int* max_combinations, const unsigned int* original_nomenclature_size)
{
    (*weights_counter)++;
    current_combination[*weights_counter] = weight;

    target -= weight;

    // если target == 0, то комбинация найдена
    if (target == 0)
    {
        // проверяем была ли такая комбинация ранее
        for (unsigned int* ptr = weights_ids_sums, *end = weights_ids_sums + *max_combinations; ptr != end; ptr++)
            if (*ptr == weight_id)
            {
                current_combination[*weights_counter] = 0;
                (*weights_counter)--;
                return;
            }

        weights_ids_sums[*number_of_combinations] = weight_id;  // если такой комбинации не было, добавляем сумму её id-шников
        (*number_of_combinations)++;                            // +1 способ получить заданный вес

        for (unsigned int i = 0; i < *max_combinations; i++)
        {
            if (combinations[i][0] != 0) continue;
            for (unsigned int j = 0; j < *original_nomenclature_size; j++)
                combinations[i][j] = current_combination[j];
            break;
        }

        current_combination[*weights_counter] = 0;
        (*weights_counter)--;

        return;
    }
    if (target < 0)     // если вес отрицателен, комбинация не найдена
    {
        current_combination[*weights_counter] = 0;
        (*weights_counter)--;

        return;
    }

    unsigned int sub_nomenclature_size_value = *nomenclature_size - 1;
    unsigned int* sub_nomenclature_size = &sub_nomenclature_size_value;     // размер новой номенклатуры 

    unsigned int* sub_nomenclature,         // массив для хранения новой номенклатуры
        * sub_weights_ids;                  // массив для хранения суммы id-шников

    for (unsigned int weight_index = 0; weight_index < *nomenclature_size; weight_index++)
    {
        sub_nomenclature = (unsigned int*)malloc(*sub_nomenclature_size * sizeof(unsigned int));
        sub_weights_ids = (unsigned int*)malloc(*sub_nomenclature_size * sizeof(unsigned int));
        if (!sub_nomenclature || !sub_weights_ids)
        {
            fprintf(stderr, "Cannot create '*sub_nomenclature' or '*sub_weights_ids' dynamic arrays [from recursive]\n");
            (*number_of_combinations) = -1;
            return;
        }

        unsigned int current_weight = nomenclature[weight_index];                   // забираем гирю из номенклатуры
        unsigned int current_weight_id = weights_ids[weight_index] + weight_id;     // id-шник этой гири

        unsigned int sub_index = 0;
        for (unsigned int weight_index_2 = 0; weight_index_2 < *nomenclature_size; weight_index_2++)
        {
            if (weight_index == weight_index_2) // гирю current_weight нужно пропустить, т.к. в новой номенклатуре её быть не должно
                continue;

            sub_nomenclature[sub_index] = nomenclature[weight_index_2];
            sub_weights_ids[sub_index] = weights_ids[weight_index_2];

            sub_index++;
        }

        // погружаемся ниже
        search_combinations_recursive(target, current_weight, current_weight_id, sub_nomenclature, sub_weights_ids, sub_nomenclature_size, current_combination, weights_counter, weights_ids_sums, number_of_combinations, combinations, max_combinations, original_nomenclature_size);
        if (*number_of_combinations == -1)  // something error
        {
            fprintf(stderr, "Something error in 'search_combinations_recursive' func [from recursive]\n");

            free(sub_weights_ids);
            free(sub_nomenclature);

            return;
        }

        free(sub_weights_ids);
        free(sub_nomenclature);
    }

    current_combination[*weights_counter] = 0;
    (*weights_counter)--;
}

/**
 * @brief Метод, который решает задачу, с помощью рекурсии
 * 
 * @param nomenclature Номенклатура гирь
 * @param nomenclature_size Размер номенклатуры гирь
 * @param target Целевой вес, для него ищем комбинации
 * @param out_combinations Итоговые комбинации гирь
 * @return int Размер массива out_combinations (по совместительству - количество комбинаций для данного целевого веса)
 */
int solution_recursive(unsigned int* nomenclature, unsigned int* nomenclature_size, unsigned int* target, unsigned int*** out_combinations)
{
    // array for weights ids
    unsigned int* weights_ids = (unsigned int*)calloc(*nomenclature_size, sizeof(unsigned int));
    if (!weights_ids)
    {
        fprintf(stderr, "Cannot create '*weights_ids' dynamic array\n");
        return -1;
    }

    // назначаем уникальные id-шники каждой гире
    //static unsigned int id = 3;
    for (unsigned int* ptr = weights_ids, *end = weights_ids + *nomenclature_size; ptr != end; ptr++)
        *ptr = (unsigned int)((next_xs64(0) / (double)RANDOM_MAX) * UINT_MAX);  // id-шник должен быть максимально уникальным, т.к. суммы не должны переплетаться

    // максимальное кол-во комбинаций
    unsigned int max_combinations_value = (unsigned int)pow(2, *nomenclature_size);
    unsigned int* max_combinations = &max_combinations_value;
    if (!max_combinations)
    {
        fprintf(stderr, "Cannot create '*max_combinations' pointer\n");
        free(weights_ids);
        return -1;
    }

    // количество комбинаций
    int number_of_combinations_value = 0;
    int* number_of_combinations = &number_of_combinations_value;
    if (!number_of_combinations)
    {
        fprintf(stderr, "Cannot create '*number_of_combinations' pointer\n");
        free(weights_ids);
        return -1;
    }

    unsigned int* weights_current_combination = (unsigned int*)calloc(*nomenclature_size, sizeof(unsigned int));    // массив с 'кандидатом' в готовую комбинацию
    if (!weights_current_combination)
    {
        fprintf(stderr, "Cannot create '*weights_current_combination' dynamic array\n");
        free(weights_ids);
        return -1;
    }

    int weight_counter_value = -1;
    int* weight_counter = &weight_counter_value;
    if (!weight_counter)
    {
        fprintf(stderr, "Cannot create '*weight_counter' pointer\n");
        free(weights_current_combination);
        free(weights_ids);
        return -1;
    }

    *out_combinations = (unsigned int**)calloc(*max_combinations, sizeof(unsigned int*)); // выделяем место для комбинаций
    if (!*out_combinations)
    {
        fprintf(stderr, "Cannot create '**out_combinations' dynamic 2D array\n");
        free(weights_current_combination);
        free(weights_ids);
        return -1;
    }

    for (unsigned int** ptr = *out_combinations, **end = *out_combinations + *max_combinations; ptr != end; ptr++)
    {
        *ptr = (unsigned int*)calloc(*nomenclature_size, sizeof(unsigned int));
        if (!ptr)
        {
            fprintf(stderr, "Cannot create '*combinations' child dynamic array\n");
            free(*out_combinations);
            free(weights_current_combination);
            free(weights_ids);
            return -1;
        }
    }

    unsigned int* weights_ids_sums = (unsigned int*)calloc(*max_combinations, sizeof(unsigned int));
    if (!weights_ids_sums)
    {
        fprintf(stderr, "Cannot create '*weights_ids_sums' dynamic array\n");

        for (unsigned int** ptr = *out_combinations, **end = *out_combinations + *max_combinations; ptr != end; ptr++)
            free(*ptr);
        free(*out_combinations);
        free(weights_current_combination);
        free(weights_ids);

        return -1;
    }

    unsigned int sub_nomenclature_size_value = *nomenclature_size - 1;
    unsigned int* sub_nomenclature_size = &sub_nomenclature_size_value;

    unsigned int* sub_nomenclature,
        * sub_weights_ids;

    for (unsigned int weight_index = 0; weight_index < *nomenclature_size; weight_index++)
    {
        sub_nomenclature = (unsigned int*)malloc(*sub_nomenclature_size * sizeof(unsigned int));
        sub_weights_ids = (unsigned int*)malloc(*sub_nomenclature_size * sizeof(unsigned int));
        if (!sub_nomenclature || !sub_weights_ids)
        {
            fprintf(stderr, "Cannot create '*sub_nomenclature' or '*sub_weights_ids' dynamic arrays\n");

            for (unsigned int** ptr = *out_combinations, **end = *out_combinations + *max_combinations; ptr != end; ptr++)
                free(*ptr);
            free(*out_combinations);
            free(weights_current_combination);
            free(weights_ids);

            return -1;
        }

        (*weight_counter) = -1; // на каждой итерации необходимо сбрасывать счётчик до -1, т.к. здесь вход в рекурсию

        unsigned int current_weight = nomenclature[weight_index];  
        unsigned int current_weight_id = weights_ids[weight_index];

        unsigned int sub_index = 0;
        for (unsigned int weight_index_2 = 0; weight_index_2 < *nomenclature_size; weight_index_2++)
        {
            if (weight_index == weight_index_2)
                continue;

            sub_nomenclature[sub_index] = nomenclature[weight_index_2];
            sub_weights_ids[sub_index] = weights_ids[weight_index_2];

            sub_index++;
        }

        // тут верх рекрсии, запускаем её
        search_combinations_recursive(*target, current_weight, current_weight_id, sub_nomenclature, sub_weights_ids, sub_nomenclature_size, weights_current_combination, weight_counter, weights_ids_sums, number_of_combinations, *out_combinations, max_combinations, nomenclature_size);        if (*number_of_combinations == -1)  // something error
        {
            fprintf(stderr, "Something error in 'search_combinations_recursive' func\n");

            free(sub_weights_ids);
            free(sub_nomenclature);

            for (unsigned int** ptr = *out_combinations, **end = *out_combinations + *max_combinations; ptr != end; ptr++)
                free(*ptr);
            free(*out_combinations);

            free(weights_current_combination);
            free(weights_ids);

            return *number_of_combinations;
        }

        free(sub_weights_ids);
        free(sub_nomenclature);
    }

    //for (unsigned int i = 0; i < *max_combinations; i++)
    //{
    //    if (combinations[i][0] != 0)
    //    {
    //        printf("\nweights_ids_sums[%u] = %10u --- combinations[%u]: ", i, weights_ids_sums[i], i);
    //        for (unsigned int j = 0; j < *nomenclature_size; j++)
    //            if (combinations[i][j] != 0)
    //                printf("%u ", combinations[i][j]);
    //    }
    //}

    // clear memory

    free(weights_current_combination);
    free(weights_ids);

    // return values
    return *number_of_combinations;
}

/**
 * @brief Вставка гири в конец curr_combination
 * 
 * @param curr_combination Массив с использоваными гирями
 * @param curr_combination_size Его размер
 * @param value Гиря, значение которой необходимо вставить в массив
 * @return int Код ошибки, вернёт 0, если нет ошибки
 */
int push_weight(unsigned int* curr_combination, unsigned int* curr_combination_size, unsigned int* value)
{
    if (!curr_combination || !curr_combination_size || !value)
    {
        fprintf(stderr, "Bad pointer: '*curr_combination' or '*curr_combination_size' or '*value'\n");
        return -1;
    }

    for (unsigned int* ptr = curr_combination; ptr != curr_combination + *curr_combination_size; ptr++)
    {
        if (*ptr)
            continue;
        *ptr = *value;
        return 0;
    }

    fprintf(stderr, "Array '*curr_combination' is full\n");
    return -1;
}

/**
 * @brief Вставка комбинации в конец combinations
 * 
 * @param combinations Массив с итоговыми комбинациями
 * @param combinations_size Его размер
 * @param curr_combination Готовая комбинация, которая была найдена ранее
 * @param original_nomenclature_size Размер этой комбинации
 * @return int Код ошибки, вернёт 0, если нет ошибки
 */
int push_combination(unsigned int*** combinations, unsigned int* combinations_size, unsigned int* curr_combination, unsigned int* original_nomenclature_size)
{
    if (!*combinations || !combinations_size || !curr_combination)
    {
        fprintf(stderr, "Bad pointer: '**combinations' or '*combinations_size' or '*curr_combination'\n");
        return -1;
    }

    for (unsigned int** combination = *combinations, **combination_end = *combinations + *combinations_size; combination != combination_end; combination++)
    {
        if (**combination)
            continue;

        for (unsigned int* ptr_c = *combination, *end_c = *combination + *original_nomenclature_size,
            *ptr_cc = curr_combination, *end_cc = curr_combination + *original_nomenclature_size;
            ptr_c != end_c && ptr_cc != end_cc;
            ptr_c++, ptr_cc++)
        {
            *ptr_c = *ptr_cc;
        }

        return 0;
    }

    fprintf(stderr, "Array '**combinations' is full\n");
    return -1;
}

/**
 * @brief Метод, который решает задачу, с помощью битов числа
 * 
 * @param nomenclature Номенклатура гирь
 * @param nomenclature_size Размер номенклатуры
 * @param target Целевой вес, для него ищем комбинации
 * @param out_combinations Итоговые комбинации гирь
 * @return int Размер массива out_combinations (по совместительству - количество комбинаций для данного целевого веса)
 */
int solution_bits(unsigned int* nomenclature, unsigned int* nomenclature_size, unsigned int* target, unsigned int*** out_combinations)
{
    if (*nomenclature_size == 0 || *nomenclature_size > (unsigned int)_allowed_bits)
    {
        fprintf(stderr, "Nomenclature size exceeds allowable value: %u\nMax allowed bits: %u\n", *nomenclature_size, _allowed_bits);
        return -1;
    }

    //// проверка на нулевой target
    //if (*target == 0)
    //{
    //    fprintf(stderr, "Zero target weight: %u\n", *target);
    //    return -1;
    //}

    // комбинатор, каждый бит в нём, это отдельная гиря
    unsigned int combinator = 1;

    unsigned int max_combinations_value = (unsigned int)pow(2, (*nomenclature_size));
    unsigned int* max_combinations = &max_combinations_value;
    if (!max_combinations)
    {
        fprintf(stderr, "Cannot create '*max_combinations' pointer\n");
        return -1;
    }

    *out_combinations = (unsigned int**)calloc(*max_combinations, sizeof(unsigned int*));
    if (!*out_combinations)
    {
        fprintf(stderr, "Cannot create '**out_combinations' 2D dynamic array\n");
        return -1;
    }

    for (unsigned int** ptr = *out_combinations, **end = *out_combinations + *max_combinations; ptr != end; ptr++)
        *ptr = (unsigned int*)calloc(*nomenclature_size, sizeof(unsigned int));

    unsigned int number_of_combinations = 0;

    while (combinator < *max_combinations)
    {
        unsigned int bit = 0;
        unsigned int combinator_copy = combinator;
        unsigned int local_target = 0;

        unsigned int* curr_combination = (unsigned int*)calloc(*nomenclature_size, sizeof(unsigned int));
        if (!curr_combination)
        {
            fprintf(stderr, "Cannot create '*curr_combination' dynamic array\n");
            return -1;
        }

        while (combinator_copy != 0)
        {
            if (combinator_copy & 1)
            {
                unsigned int weight = nomenclature[bit];
                if (weight)
                {
                    local_target += weight;
                    push_weight(curr_combination, nomenclature_size, &weight);
                }
            }

            combinator_copy >>= 1;
            bit++;
        }

        if (local_target == *target)
        {
            push_combination(out_combinations, max_combinations, curr_combination, nomenclature_size);
            number_of_combinations++;
        }

        combinator++;
        free(curr_combination);
    }

    return number_of_combinations;
}

/**
 * @brief Запускает решение в зависимости от выбранного алгоритма solution
 * 
 * @param solution Выбранный алгоритм решения
 * @param nomenclature Номенклатура гирь
 * @param nomenclature_size Размер номенклатуры
 * @param target Целевой вес, для него ищем комбинации
 * @param out_combinations Итоговые комбинации гирь
 * @return int Размер массива out_combinations (по совместительству - количество комбинаций для данного целевого веса)
 */
int get_number_of_combinations(enum Solution* solution, unsigned int* nomenclature, unsigned int* nomenclature_size, unsigned int* target, unsigned int*** out_combinations)
{
    if (!solution || !nomenclature || !nomenclature_size || !target)
    {
        fprintf(stderr, "Bad pointer: '*solution' or '*nomenclature' or '*nomenclature_size' or '*target'\n");
        return -1;
    }

    // find min_weight and weights_sum
    unsigned int min_weight = UINT_MAX,
        weights_sum = 0;

    for (unsigned int* ptr = nomenclature, *end = nomenclature + *nomenclature_size; ptr != end; ptr++)
    {
        if (*ptr && min_weight > *ptr)
            min_weight = *ptr;
        weights_sum += *ptr;
    }

    if (*target == 0)
    {
        fprintf(stderr, "Zero target weight\n");
        return -1;
    }

    if (*target < min_weight || *target > weights_sum)
        return 0;

    switch (*solution)
    {
    case RECURSIVE:
        return solution_recursive(nomenclature, nomenclature_size, target, out_combinations);
    case BITS:
        return solution_bits(nomenclature, nomenclature_size, target, out_combinations);
    }

    return -1;
}
