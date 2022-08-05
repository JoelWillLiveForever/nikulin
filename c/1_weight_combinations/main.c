/* Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм? */

#include <stdio.h>
#include <locale.h>

#define SAVED_HASHSUMS_SIZE 25 // Размер буфера, для сохранения хэш суммы найденного способа получить вес

int saved_hashsums[SAVED_HASHSUMS_SIZE];    // сохранённые хэш-суммы способов
int saved_hashsums_curr_index = 0;

int search_all_ways_recursive(int V, int sub, int sub_remains[], int sub_hash, int sub_hashes_remains[], int remains_size)
{   
    V -= sub;
    
    // условия выхода из рекурсии
    if (V == 0)
    {
        for (int i = 0; i < SAVED_HASHSUMS_SIZE; i++)
            if (saved_hashsums[i] == sub_hash) return 0;

        saved_hashsums[saved_hashsums_curr_index] = sub_hash; // сохранение хэш-суммы
        saved_hashsums_curr_index++;

        return 1;   // +1 способ найти заданный вес
    }
    if (V < 0) return 0;    // способов нет, вес отрицателен

    int ways_counter = 0;    // счётчик способов найти заданный вес
    int next_remains_size = remains_size - 1;   // размер буфера для оставшихся гирь и хэш кодов для следующей итерации рекурсии
    
    for (int i = 0; i < remains_size; i++)
    {
        int next_sub_remains[next_remains_size];        // новый буфер с оставшимися доступными гирями
        int next_sub_hashes_remains[next_remains_size]; // новый буфер с оставшимися доступными хэш кодами

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
        
        // погружение на next итерацию рекурсии
        ways_counter += search_all_ways_recursive(V, next_sub, next_sub_remains, next_sub_hash, next_sub_hashes_remains, next_remains_size);
    }

    return ways_counter;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    int weights[] = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};   // набор гирь
    int hash_codes[] = {55, 23, 421, 90, 10, 4, -8, 92, 67, 111};    // хэш коды каждой гири, соответствие по индексу

    // ввод пользователем искомого размера V в граммах
    int V;
    printf("Укажите искомый вес V в граммах из диапазона [100..11200]: ");
    scanf("%d", &V);
    
    // проверка введённого значения на принадлежность к допустимому диапазону [100..11200]
    if (V < 100 || V > 11200) 
    {
        printf("Найдено способов: 0. Указанный вами искомый веc в: %d грамм выходит за рамки допустимого диапазона [100..11200]!\n", V);
        return 0;
    }

    int ways_counter = 0;   // счётчик способов найти заданный вес
    int weights_amount = sizeof(weights) / sizeof(int); // размер массива с набором гирь
    int remains_size = weights_amount - 1;

    for (int sub_index = 0; sub_index < weights_amount; sub_index++)
    {
        int sub_remains[remains_size];          // буфер с оставшимися гирями
        int sub_hashes_remains[remains_size];   // буфер с оставшимися хэш кодами
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

        ways_counter += search_all_ways_recursive(V, sub, sub_remains, sub_hash, sub_hashes_remains, remains_size);   // запуск рекурсии
    }

    // вывод результата
    printf("Найдено способов: %d\n", ways_counter);
    return 0;
}
