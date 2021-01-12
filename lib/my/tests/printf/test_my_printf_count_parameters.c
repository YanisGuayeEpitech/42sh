/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_count_parameters function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_count_parameters, empty_fmt)
{
    cr_assert_eq(p_my_printf_count_parameters(""), 0);
}

Test(p_my_printf_count_parameters, illegal_conversions_are_skipped)
{
    cr_assert_eq(p_my_printf_count_parameters("%wx"), 0);
    cr_assert_eq(p_my_printf_count_parameters("%d%%%wx"), 2);
}

Test(p_my_printf_count_parameters, only_normal_conversions)
{
    cr_assert_eq(p_my_printf_count_parameters("%d"), 1);
    cr_assert_eq(p_my_printf_count_parameters("%d%s"), 2);
    cr_assert_eq(p_my_printf_count_parameters("%d%s%%%zu"), 4);
}

Test(p_my_printf_count_parameters, str_field_width_flags_does_not_count)
{
    cr_assert_eq(p_my_printf_count_parameters("%04zi"), 1);
    cr_assert_eq(p_my_printf_count_parameters("%#+3zi"), 1);
    cr_assert_eq(p_my_printf_count_parameters("%#+3zi%#0- +'Ihhd"), 2);
}

Test(p_my_printf_count_parameters, positional_arguments)
{
    cr_assert_eq(p_my_printf_count_parameters("%42$s"), 42);
    cr_assert_eq(p_my_printf_count_parameters("%3$s%4$d%5$c"), 5);
    cr_assert_eq(p_my_printf_count_parameters("%3$s%5$d%1$u%2$c"), 5);
    cr_assert_eq(p_my_printf_count_parameters("%dtest%1$x%2$s%x%u"), 3);
}

Test(p_my_printf_count_parameters, positional_width)
{
    cr_assert_eq(p_my_printf_count_parameters("%*42$s"), 42);
    cr_assert_eq(p_my_printf_count_parameters("%*3$s%*4$d%*5$c"), 5);
    cr_assert_eq(p_my_printf_count_parameters("%*3$s%*5$d%*1$u%*2$c"), 5);
    cr_assert_eq(p_my_printf_count_parameters("%*s%*s"), 4);
    cr_assert_eq(p_my_printf_count_parameters("%*s%*42$x%*s"), 42);
    cr_assert_eq(p_my_printf_count_parameters("%*s%*2$x%*x%*s"), 7);
    cr_assert_eq(p_my_printf_count_parameters("%2dtest%*1$x%*2$s%x%42u"), 5);
}

Test(p_my_printf_count_parameters, positional_precision)
{
    cr_assert_eq(p_my_printf_count_parameters("%.*42$s"), 42);
    cr_assert_eq(p_my_printf_count_parameters("%.*3$s%.*4$d%.*5$c"), 5);
    cr_assert_eq(p_my_printf_count_parameters("%.*3$s%.*5$d%.*1$u%.*2$c"), 5);
    cr_assert_eq(p_my_printf_count_parameters("%.*s%.*s"), 4);
    cr_assert_eq(p_my_printf_count_parameters("%.*s%.*42$x%*s"), 42);
    cr_assert_eq(p_my_printf_count_parameters("%*s%*2$x%*x%*s"), 7);
    cr_assert_eq(p_my_printf_count_parameters("%.2d%.*1$x%.*2$s%x%42u"), 5);
}

Test(p_my_printf_count_parameters, mix_n_match)
{
    cr_assert_eq(p_my_printf_count_parameters("%*.*s"), 3);
    cr_assert_eq(p_my_printf_count_parameters("%*1$.*s"), 2);
    cr_assert_eq(p_my_printf_count_parameters("%*1$.*1$s"), 1);
    cr_assert_eq(p_my_printf_count_parameters("%*1$.*3$s"), 3);
}
