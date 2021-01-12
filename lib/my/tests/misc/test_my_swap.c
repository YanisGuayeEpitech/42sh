/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_swap function
*/

#include <criterion/criterion.h>
#include "libmy/misc.h"

Test(my_swap, same_location)
{
    int a = 46;

    my_swap(&a, &a);
    cr_assert_eq(a, 46);
}

Test(my_swap, normal)
{
    int a = -789;
    int b = 67;

    my_swap(&a, &b);
    cr_assert_eq(a, 67);
    cr_assert_eq(b, -789);
}
