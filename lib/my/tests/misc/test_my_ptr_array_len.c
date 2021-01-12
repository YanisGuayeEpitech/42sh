/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_ptr_array_len function
*/

#include <criterion/criterion.h>
#include "libmy/misc.h"

Test(my_ptr_array_len, null_array)
{
    cr_assert_eq(my_ptr_array_len((const void **)NULL), 0);
}

Test(my_ptr_array_len, empty_array)
{
    char *array[] = { NULL };

    cr_assert_eq(my_ptr_array_len((const void **)array), 0);
}

Test(my_ptr_array_len, one_elem_array)
{
    char *array[] = { "TEST", NULL };

    cr_assert_eq(my_ptr_array_len((const void **)array), 1);
}

Test(my_ptr_array_len, multi_elem_array)
{
    char *array[] = { "This", "is", "a", "test", NULL };

    cr_assert_eq(my_ptr_array_len((const void **)array), 4);
}
