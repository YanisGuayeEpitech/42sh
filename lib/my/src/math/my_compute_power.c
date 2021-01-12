/*
** EPITECH PROJECT, 2020
** LibMy - math module
** File description:
** Computes nb to the power of n
*/

#include <limits.h>
#include "libmy/math.h"

MY_API int my_compute_power(int nb, int p)
{
    long long result = 1;

    if (p < 0)
        return 0;
    if (p == 0)
        return 1;
    for (int power = p; power > 0; --power) {
        result *= (long long)nb;
        if (result < (long long) INT_MIN || result > (long long)INT_MAX)
            return 0;
    }
    return (int)result;
}
