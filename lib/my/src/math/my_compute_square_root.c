/*
** EPITECH PROJECT, 2020
** LibMy - math module
** File description:
** Computes the square root of the given number
*/

#include <limits.h>
#include "libmy/math.h"

MY_API int my_compute_square_root(int nb)
{
    if (nb == 1)
        return 1;
    for (int root = 0; root < nb; ++root) {
        long long square_of_roots = root * root;

        if (square_of_roots > (long long)INT_MAX)
            return 0;
        if (square_of_roots == nb)
            return root;
    }
    return 0;
}
