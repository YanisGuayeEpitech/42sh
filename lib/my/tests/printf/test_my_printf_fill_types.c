/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_fill_types function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_fill_types, no_conversions)
{
    p_my_printf_fill_types("", NULL);
    p_my_printf_fill_types("format at end: %", NULL);
}

Test(p_my_printf_fill_types, percent_conversions)
{
    p_my_printf_arg_type_t types[3];

    p_my_printf_fill_types("test %%, %%%%, ok", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_PERCENT);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_PERCENT);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_PERCENT);
}

Test(p_my_printf_fill_types, simple_conversions)
{
    p_my_printf_arg_type_t types[7];

    p_my_printf_fill_types("%d%Lg%f%zu%0llx%Ws%04d%2.1i", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_LONG_DOUBLE);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(types[3], P_MY_PRINTF_ARG_SIZE_T);
    cr_assert_eq(types[4], P_MY_PRINTF_ARG_ULONG_LONG);
    cr_assert_eq(types[5], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[6], P_MY_PRINTF_ARG_INT);
}

Test(p_my_printf_fill_types, parametized_widths)
{
    p_my_printf_arg_type_t types[6];

    p_my_printf_fill_types("%*s%*x%*Wi%*hho", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[3], P_MY_PRINTF_ARG_UINT);
    cr_assert_eq(types[4], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[5], P_MY_PRINTF_ARG_BYTE);
}

Test(p_my_printf_fill_types, positional_widths)
{
    p_my_printf_arg_type_t types[6];

    p_my_printf_fill_types("%*5$s%*6$LA%*4$jX", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_LONG_DOUBLE);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_UINTMAX_T);
    cr_assert_eq(types[3], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[4], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[5], P_MY_PRINTF_ARG_INT);
}

Test(p_my_printf_fill_types, hybrid_widths)
{
    p_my_printf_arg_type_t types[7];

    p_my_printf_fill_types("%*s%*7$LA%*6$jX%s", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_LONG_DOUBLE);
    cr_assert_eq(types[3], P_MY_PRINTF_ARG_UINTMAX_T);
    cr_assert_eq(types[4], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[5], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[6], P_MY_PRINTF_ARG_INT);
}

Test(p_my_printf_fill_types, parametized_precisions)
{
    p_my_printf_arg_type_t types[6];

    p_my_printf_fill_types("%.*s%.*x%.*Wi%.*hho", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[3], P_MY_PRINTF_ARG_UINT);
    cr_assert_eq(types[4], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[5], P_MY_PRINTF_ARG_BYTE);
}

Test(p_my_printf_fill_types, positional_precisions)
{
    p_my_printf_arg_type_t types[6];

    p_my_printf_fill_types("%.*5$s%.*6$LA%.*4$jX", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_LONG_DOUBLE);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_UINTMAX_T);
    cr_assert_eq(types[3], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[4], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[5], P_MY_PRINTF_ARG_INT);
}

Test(p_my_printf_fill_types, hybrid_precisions)
{
    p_my_printf_arg_type_t types[7];

    p_my_printf_fill_types("%.*s%.*7$LA%.*6$jX%s", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_LONG_DOUBLE);
    cr_assert_eq(types[3], P_MY_PRINTF_ARG_UINTMAX_T);
    cr_assert_eq(types[4], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[5], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[6], P_MY_PRINTF_ARG_INT);
}

Test(p_my_printf_fill_types, fully_positional)
{
    p_my_printf_arg_type_t types[3];

    p_my_printf_fill_types("%2$*1$.*3$s", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_INT);
}

Test(p_my_printf_fill_types, hybrid)
{
    p_my_printf_arg_type_t types[3];

    p_my_printf_fill_types("%2$*.*3$s", types);
    cr_assert_eq(types[0], P_MY_PRINTF_ARG_INT);
    cr_assert_eq(types[1], P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(types[2], P_MY_PRINTF_ARG_INT);
}
