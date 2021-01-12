/*
** EPITECH PROJECT, 2020
** Libmy unit tests
** File description:
** Tests the p_my_printf_get_len_modifier function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

static p_my_printf_length_t get_len(char const **src)
{
    return p_my_printf_get_len_modifier(src);
}

Test(p_my_printf_get_len_modifier, empty_string)
{
    char const *src = "";

    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_DEFAULT);
    cr_assert_str_eq(src, "");
}

Test(p_my_printf_get_len_modifier, no_len_modifier)
{
    char const *src = "d, this is a test: %zu";

    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_DEFAULT);
    cr_assert_str_eq(src, "d, this is a test: %zu");
}

Test(p_my_printf_get_len_modifier, all_modifiers)
{
    char const *src = "hhhlllLjzt";

    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_CHAR);
    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_SHORT);
    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_LONG_LONG);
    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_LONG);
    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_LONG_DOUBLE);
    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_INTMAX_T);
    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_SIZE_T);
    cr_assert_eq(get_len(&src), P_MY_PRINTF_LEN_PTRDIFF_T);
    cr_assert_str_eq(src, "");
}
