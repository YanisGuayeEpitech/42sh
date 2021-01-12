/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_is_prime function
*/

#include <criterion/criterion.h>
#include <limits.h>
#include "libmy/math.h"

Test(my_is_prime, below_two)
{
    cr_assert(!my_is_prime(-678));
    cr_assert(!my_is_prime(0));
    cr_assert(!my_is_prime(1));
}

Test(my_is_prime, primes)
{
    cr_assert(my_is_prime(2));
    cr_assert(my_is_prime(3));
    cr_assert(my_is_prime(17));
    cr_assert(my_is_prime(INT_MAX));
}

Test(my_is_prime, non_primes)
{
    cr_assert(!my_is_prime(6));
    cr_assert(!my_is_prime(18));
    cr_assert(!my_is_prime(441));
    cr_assert(!my_is_prime(15));
    cr_assert(!my_is_prime(49));
    cr_assert(!my_is_prime(INT_MAX - 1));
}
