/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_get_conv_base function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_get_conv_base, lower_hexadecimal)
{
    char const *base;
    p_my_printf_conv_t conv = {
        .specifier = P_MY_PRINTF_SPEC_LOWER_HEXADECIMAL
    };

    cr_assert_eq(p_my_printf_get_conv_base(&conv, NULL), 16);
    cr_assert_eq(p_my_printf_get_conv_base(&conv, &base), 16);
    cr_assert_str_eq(base, "0123456789abcdef");
}

Test(p_my_printf_get_conv_base, upper_hexadecimal)
{
    char const *base;
    p_my_printf_conv_t conv = {
        .specifier = P_MY_PRINTF_SPEC_UPPER_HEXADECIMAL
    };

    cr_assert_eq(p_my_printf_get_conv_base(&conv, NULL), 16);
    cr_assert_eq(p_my_printf_get_conv_base(&conv, &base), 16);
    cr_assert_str_eq(base, "0123456789ABCDEF");
}

Test(p_my_printf_get_conv_base, decimal)
{
    char const *base;
    p_my_printf_conv_t conv = {
        .specifier = P_MY_PRINTF_SPEC_SIGNED
    };

    cr_assert_eq(p_my_printf_get_conv_base(&conv, NULL), 10);
    cr_assert_eq(p_my_printf_get_conv_base(&conv, &base), 10);
    cr_assert_str_eq(base, "0123456789");
}

Test(p_my_printf_get_conv_base, octal)
{
    char const *base;
    p_my_printf_conv_t conv = {
        .specifier = P_MY_PRINTF_SPEC_OCTAL
    };

    cr_assert_eq(p_my_printf_get_conv_base(&conv, NULL), 8);
    cr_assert_eq(p_my_printf_get_conv_base(&conv, &base), 8);
    cr_assert_str_eq(base, "01234567");
}
