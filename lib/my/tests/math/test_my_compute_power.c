/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests my_compute_power_* functions
*/

#include <criterion/criterion.h>
#include <limits.h>
#include "libmy/math.h"

Test(my_compute_power, n_power_zero)
{
    cr_assert_eq(my_compute_power(-6, 0), 1);
    cr_assert_eq(my_compute_power(0, 0), 1);
    cr_assert_eq(my_compute_power(42, 0), 1);
}

Test(my_compute_power, negative_power)
{
    cr_assert_eq(my_compute_power(41, -1), 0);
}

Test(my_compute_power, powers_of_two)
{
    cr_assert_eq(my_compute_power(2, 4), 16);
    cr_assert_eq(my_compute_power(2, 6), 64);
}

Test(my_compute_power, overflow)
{
    cr_assert_eq(my_compute_power(INT_MAX, INT_MAX), 0);
}
