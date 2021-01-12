/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_next_conversion function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_next_conversion, empty_string)
{
    char const *str = "";

    cr_assert_eq(p_my_printf_next_conversion(&str), 0);
    cr_assert_str_eq(str, "");
}

Test(p_my_printf_next_conversion, normal_string)
{
    char const *str = "This is a test";

    cr_assert_eq(p_my_printf_next_conversion(&str), 0);
    cr_assert_str_eq(str, "");
}

Test(p_my_printf_next_conversion, escaped_percent)
{
    char const *str = "4 %% 2";

    cr_assert_eq(p_my_printf_next_conversion(&str), 3);
    cr_assert_str_eq(str, "% 2");
}

Test(p_my_printf_next_conversion, escaped_percent_followed_by_conversion)
{
    char const *str = "output: %%%f\n";

    cr_assert_eq(p_my_printf_next_conversion(&str), 9);
    cr_assert_str_eq(str, "%%f\n");
    cr_assert_eq(p_my_printf_next_conversion(&str), 1);
    cr_assert_str_eq(str, "%f\n");
    cr_assert_eq(p_my_printf_next_conversion(&str), 1);
    cr_assert_str_eq(str, "f\n");
}

Test(p_my_printf_next_conversion, empty_conversion)
{
    char const *str = "output: %";

    cr_assert_eq(p_my_printf_next_conversion(&str), 0);
    cr_assert_str_eq(str, "");
}

Test(p_my_printf_next_conversion, multi_conversions)
{
    char const *str = "%s%f%%%dtest%zu\n%016s";

    cr_assert_eq(p_my_printf_next_conversion(&str), 1);
    cr_assert_str_eq(str, "s%f%%%dtest%zu\n%016s");
    cr_assert_eq(p_my_printf_next_conversion(&str), 2);
    cr_assert_str_eq(str, "f%%%dtest%zu\n%016s");
    cr_assert_eq(p_my_printf_next_conversion(&str), 2);
    cr_assert_str_eq(str, "%%dtest%zu\n%016s");
    cr_assert_eq(p_my_printf_next_conversion(&str), 1);
    cr_assert_str_eq(str, "%dtest%zu\n%016s");
    cr_assert_eq(p_my_printf_next_conversion(&str), 1);
    cr_assert_str_eq(str, "dtest%zu\n%016s");
    cr_assert_eq(p_my_printf_next_conversion(&str), 6);
    cr_assert_str_eq(str, "zu\n%016s");
    cr_assert_eq(p_my_printf_next_conversion(&str), 4);
    cr_assert_str_eq(str, "016s");
    cr_assert_eq(p_my_printf_next_conversion(&str), 0);
    cr_assert_str_eq(str, "");
}
