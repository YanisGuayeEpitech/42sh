/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_get_conv_specifier function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

static p_my_printf_specifier_t get_conv(char const **src)
{
    return p_my_printf_get_conv_specifier(src);
}

Test(p_my_printf_get_conv_specifier, empty_string)
{
    char const *src = "";
    char const *original = src;

    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_NONE);
    cr_assert_eq(src, original);
}

Test(p_my_printf_get_conv_specifier, invalid_specifiers)
{
    char const *src = "wqMkvend";

    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_NONE);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_NONE);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_NONE);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_NONE);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_NONE);
    cr_assert_str_eq(src, "end");
}

Test(p_my_printf_get_conv_specifier, valid_specifiers)
{
    char const *src = "duoxXfFeEgGaAcspnend";

    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_SIGNED);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_UNSIGNED);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_OCTAL);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_LOWER_HEXADECIMAL);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_UPPER_HEXADECIMAL);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_LOWER_FLOAT);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_UPPER_FLOAT);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_LOWER_FLOAT_EXPONENT);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_UPPER_FLOAT_EXPONENT);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_LOWER_FLOAT_SCIENTIFIC);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_UPPER_FLOAT_SCIENTIFIC);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_LOWER_FLOAT_HEXADECIMAL);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_UPPER_FLOAT_HEXADECIMAL);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_CHAR);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_STRING);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_POINTER);
    cr_assert_eq(get_conv(&src), P_MY_PRINTF_SPEC_COUNT);
    cr_assert_str_eq(src, "end");
}
