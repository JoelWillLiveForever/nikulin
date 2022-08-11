#include <stddef.h>

class WeightsCombinator
{
private:
    const char allowed_bits = sizeof(unsigned int) * 8;         // максимальное количество гирь, которое можно задать

    int* my_weights;                                            // указатель на первый элемент массива гирь
    size_t my_weights_size;                                     // размер массива гирь

public:
    WeightsCombinator(int* weights, size_t weights_size);       // конструктор класса

    void set_weights(int* weights, size_t weights_size);        // set-метод для массива гирь
    int* get_weights();                                         // get-метод для массива гирь
                                                                
    size_t get_weights_size();                                  // get-метод для размера массива гирь

    int combine(int target);                                    // метод поиска комбинаций для заданного веса
};
