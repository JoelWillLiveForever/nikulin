#include "xor_shift_1024__generator_class.hpp"

unsigned long long XORShift1024_Generator::next()
{
    unsigned long long s0 = S[i];

    ++i &= 15;  // обновление индекса: i = (i + 1) & 15

    unsigned long long s1 = S[i];

    s1 ^= (s1 << 31);
    s1 ^= (s1 >> 11);
    s0 ^= (s0 >> 30);

    S[i] = s0 ^ s1;
   
    return S[i] * 1'181'783'497'276'652'981ULL;
}
