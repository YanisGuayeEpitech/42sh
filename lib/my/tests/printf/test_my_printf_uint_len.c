/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_uint_len function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_uint_len, lower_hexadecimal_no_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 0x539e7 },
        .specifier = P_MY_PRINTF_SPEC_LOWER_HEXADECIMAL,
        .flags = 0,
        .precision = 0
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 5);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_uint_len, upper_hexadecimal_no_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 0x0 },
        .specifier = P_MY_PRINTF_SPEC_UPPER_HEXADECIMAL,
        .flags = 0,
        .precision = 0
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 1);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_uint_len, decimal_no_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 42 },
        .specifier = P_MY_PRINTF_SPEC_UNSIGNED,
        .flags = 0,
        .precision = 0
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 2);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_uint_len, octal_no_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 0153771 },
        .specifier = P_MY_PRINTF_SPEC_OCTAL,
        .flags = 0,
        .precision = 0
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 6);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_uint_len, decimal_small_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 1234 },
        .specifier = P_MY_PRINTF_SPEC_UNSIGNED,
        .flags = P_MY_PRINTF_FLAG_HAS_PRECISION,
        .precision = 2
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 4);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_uint_len, decimal_big_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 1234 },
        .specifier = P_MY_PRINTF_SPEC_UNSIGNED,
        .flags = P_MY_PRINTF_FLAG_HAS_PRECISION,
        .precision = 8
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 8);
    cr_assert_eq(zeros, 4);
}

Test(p_my_printf_uint_len, hexadecimal_big_precision)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 0x1234 },
        .specifier = P_MY_PRINTF_SPEC_LOWER_HEXADECIMAL,
        .flags = P_MY_PRINTF_FLAG_HAS_PRECISION,
        .precision = 8
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 8);
    cr_assert_eq(zeros, 4);
}

Test(p_my_printf_uint_len, lower_hexadecimal_alt)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 0x539e7 },
        .specifier = P_MY_PRINTF_SPEC_LOWER_HEXADECIMAL,
        .flags = P_MY_PRINTF_FLAG_ALT,
        .precision = 0
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 7);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_uint_len, upper_hexadecimal_alt)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 0x0 },
        .specifier = P_MY_PRINTF_SPEC_UPPER_HEXADECIMAL,
        .flags = P_MY_PRINTF_FLAG_ALT,
        .precision = 0
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 3);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_uint_len, decimal_alt)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 69420 },
        .specifier = P_MY_PRINTF_SPEC_UNSIGNED,
        .flags = P_MY_PRINTF_FLAG_ALT,
        .precision = 0
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 5);
    cr_assert_eq(zeros, 0);
}

Test(p_my_printf_uint_len, octal_alt)
{
    p_my_printf_conv_t conv = {
        .value = { .uint_arg = 0153771 },
        .specifier = P_MY_PRINTF_SPEC_OCTAL,
        .flags = P_MY_PRINTF_FLAG_ALT,
        .precision = 0
    };
    size_t zeros = 0;

    cr_assert_eq(p_my_printf_uint_len(&conv, &zeros), 7);
    cr_assert_eq(zeros, 0);
}
