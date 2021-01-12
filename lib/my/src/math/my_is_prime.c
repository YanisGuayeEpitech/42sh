/*
** EPITECH PROJECT, 2020
** LibMy - math module
** File description:
** Tests whether the passed number is prime
*/

#include "libmy/math.h"

MY_API int my_is_prime(int nb)
{
    if (nb <= 3)
        return nb > 1;
    if (!(nb % 2) || !(nb % 3))
        return 0;
    for (int n = 5; (long long)n * (long long)n < (long long)nb; n += 6) {
        if (!(nb % n) || !(nb % (n + 2)))
            return 0;
    }
    return 1;
}
