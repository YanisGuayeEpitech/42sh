/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_get_position function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_get_position, not_an_index)
{
    char const *src = "test";
    size_t pos = 0;

    cr_assert_neq(p_my_printf_get_position(&src, &pos), 0);
}

Test(p_my_printf_get_position, index_without_terminator)
{
    char const *src = "1234";
    size_t pos = 0;

    cr_assert_neq(p_my_printf_get_position(&src, &pos), 0);
}

Test(p_my_printf_get_position, regular_index)
{
    char const *src = "1234$end";
    size_t pos = 0;

    cr_assert_eq(p_my_printf_get_position(&src, &pos), 0);
    cr_assert_eq(pos, 1233);
    cr_assert_str_eq(src, "end");
}
