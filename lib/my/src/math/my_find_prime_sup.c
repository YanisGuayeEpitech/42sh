/*
** EPITECH PROJECT, 2020
** LibMy - math module
** File description:
** Returns the closest prime number that is greater than, or equal to n
*/

#include <limits.h>
#include "libmy/math.h"

MY_API int my_find_prime_sup(int nb)
{
    int n = nb < 2 ? 2 : nb;

    while (!my_is_prime(n))
        ++n;
    return n;
}
