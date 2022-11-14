#include "../stable.h"  // C precompiled headers

#include "wc_module.h"
#include "../random/src/xor_shift.h"

void search_combinations_recursive(unsigned int target, unsigned int weight, unsigned int weight_id, unsigned int* nomenclature, unsigned int* weights_ids, unsigned int* nomenclature_size, unsigned int* current_combination, int* weights_counter, unsigned int* weights_ids_sums, int* number_of_combinations, unsigned int** combinations, unsigned int* max_combinations, const unsigned int* original_nomenclature_size)
{
    (*weights_counter)++;
    current_combination[*weights_counter] = weight;

    target -= weight;

    // условия выхода из рекурсии
    if (target == 0)
    {
        for (unsigned int *ptr = weights_ids_sums, *end = weights_ids_sums + *max_combinations; ptr != end; ptr++)
            if (*ptr == weight_id) 
            { 
                current_combination[*weights_counter] = 0; 
                (*weights_counter)--; 
                return; 
            }

        weights_ids_sums[*number_of_combinations] = weight_id;  // сохранение суммы id-шников
        (*number_of_combinations)++;                            // +1 способ найти заданный вес

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
    if (target < 0)     // способов нет, вес отрицателен
    { 
        current_combination[*weights_counter] = 0; 
        (*weights_counter)--; 
        
        return; 
    }

    unsigned int sub_nomenclature_size_value = *nomenclature_size - 1;
    unsigned int* sub_nomenclature_size = &sub_nomenclature_size_value;      // новый размер sub-номенклатуры

    unsigned int* sub_nomenclature,         // новая номенлатура с оставшимися доступными гирями
                * sub_weights_ids;          // новый массив с оставшимися доступными id-шниками

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

        unsigned int current_weight = nomenclature[weight_index];                   // эта гиря сейчас выбрана
        unsigned int current_weight_id = weights_ids[weight_index] + weight_id;     // берём id-шник выбранной гири и увеличиваем сумму id-шников

        unsigned int sub_index = 0;
        for (unsigned int weight_index_2 = 0; weight_index_2 < *nomenclature_size; weight_index_2++)
        {
            if (weight_index == weight_index_2) // мы уже взяли эту гирю => она не входит в новую номенклатуру
                continue;

            sub_nomenclature[sub_index] = nomenclature[weight_index_2];
            sub_weights_ids[sub_index] = weights_ids[weight_index_2];

            sub_index++;
        }

        // погружение на next итерацию рекурсии
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

int solution_recursive(unsigned int* nomenclature, unsigned int* nomenclature_size, unsigned int* target, unsigned int*** out_combinations)
{
    // для каждой гири будет свой id, даже если веса одинаковы
    unsigned int* weights_ids = (unsigned int*)calloc(*nomenclature_size, sizeof(unsigned int));
    if (!weights_ids)
    {
        fprintf(stderr, "Cannot create '*weights_ids' dynamic array\n");
        return -1;
    }

    // назначаем id-шники гирям
    //static unsigned int id = 3;
    for (unsigned int* ptr = weights_ids, *end = weights_ids + *nomenclature_size; ptr != end; ptr++)
        *ptr = (unsigned int)((next_xs64(0) / (double)RANDOM_MAX) * UINT_MAX);  // каждый id должен быть максимально уникален, чтобы снизить риск выпадения одинаковой суммы

    // максиммальное число комбинаций
    unsigned int max_combinations_value = (unsigned int)pow(2, *nomenclature_size);
    unsigned int* max_combinations = &max_combinations_value;
    if (!max_combinations)
    {
        fprintf(stderr, "Cannot create '*max_combinations' pointer\n");
        free(weights_ids);
        return -1;
    }

    // счётчик комбинаций
    int number_of_combinations_value = 0;
    int* number_of_combinations = &number_of_combinations_value;
    if (!number_of_combinations)
    {
        fprintf(stderr, "Cannot create '*number_of_combinations' pointer\n");
        free(weights_ids);
        return -1;
    }

    unsigned int* weights_current_combination = (unsigned int*)calloc(*nomenclature_size, sizeof(unsigned int));    // кандидат в комбинацию, тут хранятся использованные гири
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

    *out_combinations = (unsigned int**)calloc(*max_combinations, sizeof(unsigned int*)); // двумерный массив с комбинациями
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

    unsigned int* weights_ids_sums = (unsigned int*)calloc(*max_combinations, sizeof(unsigned int)); // сохранённые суммы id-шников для каждой комбинации
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

    unsigned int* sub_nomenclature,     // буфер с оставшимися гирями
                * sub_weights_ids;      // буфер с оставшимися id-шниками гирь

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

        (*weight_counter) = -1; // сбрасываем счётчик использованных гирь каждую итерацию, т.к. здесь начало рекурсии

        unsigned int current_weight = nomenclature[weight_index];       // эта гиря сейчас выбрана
        unsigned int current_weight_id = weights_ids[weight_index];     // берём id-шник выбранной гири и увеличиваем сумму id-шников

        unsigned int sub_index = 0;
        for (unsigned int weight_index_2 = 0; weight_index_2 < *nomenclature_size; weight_index_2++)
        {
            if (weight_index == weight_index_2) // мы уже взяли эту гирю => она не входит в новую номенклатуру
                continue;

            sub_nomenclature[sub_index] = nomenclature[weight_index_2];
            sub_weights_ids[sub_index] = weights_ids[weight_index_2];

            sub_index++;
        }

        search_combinations_recursive(*target, current_weight, current_weight_id, sub_nomenclature, sub_weights_ids, sub_nomenclature_size, weights_current_combination, weight_counter, weights_ids_sums, number_of_combinations, *out_combinations, max_combinations, nomenclature_size);   // запуск рекурсии
        if (*number_of_combinations == -1)  // something error
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

int push_weight(unsigned int* curr_combination, unsigned int* curr_combination_size, unsigned int* value)
{
    if (!curr_combination || !curr_combination_size || !value)
    {
        fprintf(stderr, "Bad pointer: '*curr_combination' or '*curr_combination_size' or '*value'\n");
        return -1;
    }

    // вставить в конец массива значение
    for (unsigned int* ptr = curr_combination; ptr != curr_combination + *curr_combination_size; ptr++)
    {
        // если в ячейке массива уже есть значение
        if (*ptr)
            continue;

        // если в ячейке ноль
        *ptr = *value;
        return 0;
    }

    // если дошли до сюда, значит места в массиве нет
    fprintf(stderr, "Array '*curr_combination' is full\n");
    return -1;
}

int push_combination(unsigned int*** combinations, unsigned int* combinations_size, unsigned int* curr_combination, unsigned int* original_nomenclature_size)
{
    if (!*combinations || !combinations_size || !curr_combination)
    {
        fprintf(stderr, "Bad pointer: '**combinations' or '*combinations_size' or '*curr_combination'\n");
        return -1;
    }

    // вставить в конец массива значение
    for (unsigned int** combination = *combinations, **combination_end = *combinations + *combinations_size; combination != combination_end; combination++)
    {
        // если в ячейке массива уже есть значение
        if (**combination)
            continue;

        // если в ячейке ноль
        for (unsigned int* ptr_c = *combination, *end_c = *combination + *original_nomenclature_size,
            *ptr_cc = curr_combination, *end_cc = curr_combination + *original_nomenclature_size;
            ptr_c != end_c && ptr_cc != end_cc;
            ptr_c++, ptr_cc++)
        {
            *ptr_c = *ptr_cc;
        }

        return 0;
    }

    // если дошли до сюда, значит места в массиве нет
    fprintf(stderr, "Array '**combinations' is full\n");
    return -1;
}

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

    // число для проверки комбинаций гирь, с помощью битов числа
    unsigned int combinator = 1;

    // максиммальное число комбинаций и итератор на номенклатуру весов
    unsigned int max_combinations_value = (unsigned int)pow(2, (*nomenclature_size));
    unsigned int* max_combinations = &max_combinations_value;
    if (!max_combinations)
    {
        fprintf(stderr, "Cannot create '*max_combinations' pointer\n");
        return -1;
    }

    *out_combinations = (unsigned int**)calloc(*max_combinations, sizeof(unsigned int*)); // массив с комбинациями
    if (!*out_combinations)
    {
        fprintf(stderr, "Cannot create '**out_combinations' 2D dynamic array\n");
        return -1;
    }

    for (unsigned int** ptr = *out_combinations, **end = *out_combinations + *max_combinations; ptr != end; ptr++)
        *ptr = (unsigned int*)calloc(*nomenclature_size, sizeof(unsigned int));

    unsigned int number_of_combinations = 0;

    // проходимся по всем уникальным комбинациям, увеличивая combinator на 1
    while (combinator < *max_combinations)
    {
        unsigned int bit = 0; // номер проверяемого бита + по совместительству индекс гири
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
                // получить размер гири из массива гирь, если бит равен 1
                unsigned int weight = nomenclature[bit];
                if (weight)
                {
                    local_target += weight;
                    push_weight(curr_combination, nomenclature_size, &weight);
                }
            }

            combinator_copy >>= 1; // сместить отсавшиеся биты вправо
            bit++;
        }

        // если текущая комбинация дала необходимый вес, то сохранить комбинацию
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

    // если целевой вес вне допустимого диапазона, вернуть 0 комбинаций
    for (unsigned int* ptr = nomenclature, *end = nomenclature + *nomenclature_size; ptr != end; ptr++)
    {
        if (*ptr && min_weight > *ptr)
            min_weight = *ptr;
        weights_sum += *ptr;
    }

    if (*target == 0)   // вес не должен быть нулевым
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

    return -1;  // что-то пошло не так
}