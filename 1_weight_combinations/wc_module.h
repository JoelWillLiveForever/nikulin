#ifndef __WC_MODULE_H__ // Include Guard
#define __WC_MODULE_H__

enum Solution
{
    RECURSIVE,
    BITS
};

static const char _allowed_bits = sizeof(unsigned int) * 8;

// TODO: расставить const
int get_number_of_combinations(enum Solution* solution, unsigned int* nomenclature, unsigned int* nomenclature_size, unsigned int* target, unsigned int*** out_combinations);

#endif