/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_compute_square_root function
*/

#include <criterion/criterion.h>
#include <limits.h>
#include "libmy/math.h"

Test(my_compute_square_root, zero_or_negative)
{
    cr_assert_eq(my_compute_square_root(0), 0);
    cr_assert_eq(my_compute_square_root(-7), 0);
}

Test(my_compute_square_root, numbers_with_integral_root)
{
    cr_assert_eq(my_compute_square_root(1), 1);
    cr_assert_eq(my_compute_square_root(4), 2);
    cr_assert_eq(my_compute_square_root(93025), 305);
}

Test(my_compute_square_root, number_with_no_integral_root)
{
    cr_assert_eq(my_compute_square_root(2), 0);
    cr_assert_eq(my_compute_square_root(15), 0);
    cr_assert_eq(my_compute_square_root(INT_MAX), 0);
}
