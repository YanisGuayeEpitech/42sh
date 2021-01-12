/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_sort_int_array_function
*/

#include <criterion/criterion.h>
#include "libmy/misc.h"

Test(my_sort_int_array, null_array)
{
    my_sort_int_array(NULL, 0);
    my_sort_int_array(NULL, 67);
}

Test(my_sort_int_array, one_elem)
{
    int array[] = { 42 };

    my_sort_int_array(array, 1);
    cr_assert_eq(array[0], 42);
}

Test(my_sort_int_array, three_elems_sorted)
{
    int array[] = { 1, 2, 3 };

    my_sort_int_array(array, 3);
    cr_assert_eq(array[0], 1);
    cr_assert_eq(array[1], 2);
    cr_assert_eq(array[2], 3);
}

Test(my_sort_int_array, three_elems_unsorted)
{
    int array[] = { 76, -123, 89 };

    my_sort_int_array(array, 3);
    cr_assert_eq(array[0], -123);
    cr_assert_eq(array[1], 76);
    cr_assert_eq(array[2], 89);
}
