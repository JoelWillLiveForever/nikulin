#include <stdio.h>
#include <locale.h>

/* Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм? */

#define SAVED_HASHSUMS_SIZE 100 // Размер буфера, для сохранения хэш суммы найденного способа получить вес

int main()
{
    setlocale(LC_ALL, "Rus");

    int weights[] = {100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000};   // набор гирь
    int hash_codes[] = {55, 23, 421, 90, 10, 4, -8, 92, 67, 111};    // хэш коды каждой гири, соответствие по индексу

    for (int i = 0; i < 10; i++)
        printf("\nХэш код в соответствии с каждой гирей. Гиря: %4d == Хэш: %4d", weights[i], hash_codes[i]);

    // ввод пользователем искомого размера V в граммах
    int V;
    printf("\nУкажите искомый вес V в граммах из диапазона [100..11200]: ");
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
    int saved_hashes[25];

    // новый алгоритм
    for (int ri = 0; ri < weights_amount; ri++)
    {
        for (int remains = 0; remains < 9; remains++)
        {
            int new_V = weights[ri];
            int hash = hash_codes[ri];
            for (int si = 0; si < remains; si++)
            {
                if (ri == si) continue;
               
                new_V += weights[si];
                hash += hash_codes[si];

                if (new_V == V) break;
            }

            if (new_V == V) 
            {
                bool was = false;
                for (int hi = 0; hi < 25; hi++)
                    if (saved_hashes[hi] == hash)
                    {
                        was = true;
                        break;
                    }

                if (!was) 
                {
                    ways_counter++;
                    saved_hashes[ways_counter-1] = hash;
                }
            }
        }
    }


    // вывод результата
    printf("\n\nНайдено способов: %d\n", ways_counter);
    return 0;
}
