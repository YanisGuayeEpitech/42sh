/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_conversion_len function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_conversion_len, illegal_conv_type)
{
    p_my_printf_conv_t conv = {
        .type = P_MY_PRINTF_ARG_STRING + 1
    };
    size_t zeros;

    cr_assert_eq(p_my_printf_conversion_len(&conv, &zeros), 0);
}
