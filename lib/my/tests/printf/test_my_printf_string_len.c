/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_string_len function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_string_len, null_string)
{
    p_my_printf_conv_t conv = {
        .value = { .string_arg = NULL },
        .type = P_MY_PRINTF_ARG_STRING
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_string_len(&conv, &zeros), 6);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_string_len, regular_string)
{
    p_my_printf_conv_t conv = {
        .value = { .string_arg = "This is a test" },
        .type = P_MY_PRINTF_ARG_STRING
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_string_len(&conv, &zeros), 14);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_string_len, small_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .string_arg = "This is a test" },
        .type = P_MY_PRINTF_ARG_STRING,
        .flags = P_MY_PRINTF_FLAG_HAS_PRECISION,
        .precision = 4
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_string_len(&conv, &zeros), 4);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_string_len, big_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .string_arg = "Yeet!" },
        .type = P_MY_PRINTF_ARG_STRING,
        .flags = P_MY_PRINTF_FLAG_HAS_PRECISION,
        .precision = 10
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_string_len(&conv, &zeros), 5);
    cr_assert_eq(zeros, 0);
}
