/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_strdup function
*/

#include <criterion/criterion.h>
#include <stddef.h>
#include "libmy/ascii.h"

Test(my_strdup, null_string)
{
    cr_assert_eq(my_strdup(NULL), NULL);
}

Test(my_strdup, empty_string)
{
    char *src = "";
    char *dup = my_strdup(src);

    cr_assert_neq(src, dup);
    cr_assert_str_eq(src, dup);
}

Test(my_strdup, regular_string)
{
    char *src = "This is a test";
    char *dup = my_strdup(src);

    cr_assert_neq(src, dup);
    cr_assert_str_eq(src, dup);
}
