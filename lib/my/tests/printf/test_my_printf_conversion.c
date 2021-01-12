/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_conversion function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_conversion, illegal_conv_type)
{
    p_my_printf_conv_t conv = {
        .type = P_MY_PRINTF_ARG_STRING + 1
    };

    cr_assert_lt(p_my_printf_conversion(NULL, &conv, 0), 0);
}
