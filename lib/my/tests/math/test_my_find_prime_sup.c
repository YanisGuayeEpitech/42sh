/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_find_prime_sup function
*/

#include <criterion/criterion.h>
#include <limits.h>
#include "libmy/math.h"

Test(my_find_prime_sup, under_two)
{
    cr_assert_eq(my_find_prime_sup(-67), 2);
    cr_assert_eq(my_find_prime_sup(-1), 2);
    cr_assert_eq(my_find_prime_sup(0), 2);
    cr_assert_eq(my_find_prime_sup(1), 2);
}

Test(my_find_prime_sup, primes)
{
    cr_assert_eq(my_find_prime_sup(2), 2);
    cr_assert_eq(my_find_prime_sup(13), 13);
    cr_assert_eq(my_find_prime_sup(INT_MAX), INT_MAX);
}

Test(my_find_prime_sup, non_primes)
{
    cr_assert_eq(my_find_prime_sup(14), 17);
    cr_assert_eq(my_find_prime_sup(INT_MAX - 1), INT_MAX);
}
