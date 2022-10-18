/* Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм? */

#include "../pch.h"
// #include <locale.h>

#define SAVED_HASHSUMS_SIZE 100 // Размер буфера, для сохранения хэш суммы найденного способа получить вес

int saved_roots[10];   // сохранённые комбинации гирь
int counter = -1;

int saved[SAVED_HASHSUMS_SIZE][10];

int saved_hashsums[SAVED_HASHSUMS_SIZE];    // сохранённые хэш-суммы способов
int saved_hashsums_curr_index = 0;

int search_all_ways_recursive(int V, int sub, int sub_remains[], int sub_hash, int sub_hashes_remains[], int remains_size)
{   
    counter++;
    saved_roots[counter] = sub;

    //printf("\nV before = %d", V);
    //printf("\nsub = %d", sub);

    V -= sub;
    //printf("\nV after = %d", V);
    
    // условия выхода из рекурсии
    if (V == 0)
    {
        for (int i = 0; i < SAVED_HASHSUMS_SIZE; i++)
            if (saved_hashsums[i] == sub_hash) { saved_roots[counter] = 0; counter--; return 0; }

        saved_hashsums[saved_hashsums_curr_index] = sub_hash; // сохранение хэш-суммы
        saved_hashsums_curr_index++;

        for (int i = 0; i < SAVED_HASHSUMS_SIZE; i++)
        {
            if (saved[i][0] != 0) continue;
            for (int j = 0; j < 10; j++) 
                saved[i][j] = saved_roots[j];
            break;
        }

        saved_roots[counter] = 0;
        counter--;

        return 1;   // +1 способ найти заданный вес
    }
    if (V < 0) { saved_roots[counter] = 0; counter--; return 0; }    // способов нет, вес отрицателен

    int ways_counter = 0;    // счётчик способов найти заданный вес
    int next_remains_size = remains_size - 1;   // размер буфера для оставшихся гирь и хэш кодов для следующей итерации рекурсии
    
    int *next_sub_remains,          // новый буфер с оставшимися доступными гирями
        *next_sub_hashes_remains;   // новый буфер с оставшимися доступными хэш кодами

    for (int i = 0; i < remains_size; i++)
    {
        next_sub_remains = (int *) malloc(next_remains_size * sizeof(int));       
        next_sub_hashes_remains = (int *) malloc(next_remains_size * sizeof(int));

        int remains_curr_index = 0;

        for (int j = 0; j < remains_size; j++)
        {
            if (i == j) continue;
            
            // заполнение новых буферов
            next_sub_remains[remains_curr_index] = sub_remains[j];
            next_sub_hashes_remains[remains_curr_index] = sub_hashes_remains[j];

            remains_curr_index++;
        }

        int next_sub = sub_remains[i];                          // следующая гиря в цепочке гиря
        int next_sub_hash = sub_hash + sub_hashes_remains[i];   // хэш-сумма всех имеющихся гирь в цепочке
        
        //int old = ways_counter;
        // погружение на next итерацию рекурсии
        ways_counter += search_all_ways_recursive(V, next_sub, next_sub_remains, next_sub_hash, next_sub_hashes_remains, next_remains_size);
        
        free(next_sub_remains);
        free(next_sub_hashes_remains);
    }

    saved_roots[counter] = 0;
    counter--;

    return ways_counter;
}

int main()
{
    // setlocale(LC_ALL, "Rus");

    int weights[] = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};   // набор гирь
    int hash_codes[] = {55, 23, 421, 90, 10, 4, -8, 92, 67, 111};    // хэш коды каждой гири, соответствие по индексу

    for (int i = 0; i < 10; i++)
        printf("\nWeight: %4d == Hash: %4d", weights[i], hash_codes[i]);

    // ввод пользователем искомого размера V в граммах
    int V;
    printf("\n\nSpecified desired weight V in grams from range [100..11200]: ");
    scanf("%d", &V);
    
    // проверка введённого значения на принадлежность к допустимому диапазону [100..11200]
    if (V < 100 || V > 11200) 
    {
        printf("Combinations: 0. Weight: %d out of range [100..11200]!\n", V);
        return 0;
    }

    int ways_counter = 0;   // счётчик способов найти заданный вес
    int weights_amount = sizeof(weights) / sizeof(int); // размер массива с набором гирь
    int remains_size = weights_amount - 1;

    int *sub_remains,           // буфер с оставшимися гирями
        *sub_hashes_remains;    // буфер с оставшимися хэш кодами

    printf("\n");
    for (int sub_index = 0; sub_index < weights_amount; sub_index++)
    {
        //printf("\n\nV = %d", V);
        //printf("\nsub = %d", weights[sub_index]);

        sub_remains = (int *) malloc( sizeof(int) * remains_size);       
        sub_hashes_remains = (int *) malloc( sizeof(int) * remains_size);

        int remains_curr_index = 0;

        for (int j = 0; j < weights_amount; j++)
        {
            if (sub_index == j) continue;

            // заполнение буферов
            sub_remains[remains_curr_index] = weights[j];
            sub_hashes_remains[remains_curr_index] = hash_codes[j];

            remains_curr_index++;
        }

        int sub = weights[sub_index];           // выбранная гиря
        int sub_hash = hash_codes[sub_index];    // хэш код выбранной гири
        
        //saved_roots[counter] = sub;
        //counter++;
        counter = -1;

        ways_counter += search_all_ways_recursive(V, sub, sub_remains, sub_hash, sub_hashes_remains, remains_size);   // запуск рекурсии

        free(sub_remains);
        free(sub_hashes_remains);
    }

    for (int i = 0; i < SAVED_HASHSUMS_SIZE; i++) 
    {
        if (saved[i][0] != 0) 
        {
            printf("\nsaved_hashsums[%d] = %6d\tsaved_roots[%d]: ", i, saved_hashsums[i], i);
            for (int j = 0; j < 10; j++)
                if (saved[i][j] != 0)
                    printf("%6d", saved[i][j]);
        }
    }

    // вывод результата
    printf("\n\nCombinations: %d\n", ways_counter);
    return 0;
}