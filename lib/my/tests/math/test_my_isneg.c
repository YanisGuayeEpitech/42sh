/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_isneg function
*/

#include <criterion/criterion.h>
#include "libmy/math.h"

Test(my_isneg, positives)
{
    cr_assert_eq(!my_isneg(67), 1);
    cr_assert_eq(!my_isneg(56484), 1);
}

Test(my_isneg, negatives)
{
    cr_assert_eq(!!my_isneg(-1), 1);
    cr_assert_eq(!!my_isneg(-783614), 1);
}

Test(my_isneg, zero)
{
    cr_assert_eq(!my_isneg(0), 1);
}
