/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_get_flags function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_get_flags, empty_string)
{
    char const *str = "";

    cr_assert_eq(p_my_printf_get_flags(&str), 0);
    cr_assert_str_eq(str, "");
}

Test(p_my_printf_get_flags, unsupported_flags)
{
    char const *str = "vxTz";

    cr_assert_eq(p_my_printf_get_flags(&str), 0);
    cr_assert_str_eq(str, "vxTz");
}

Test(p_my_printf_get_flags, all_flags)
{
    char const *str = "0-I' +#after";
    int flags = P_MY_PRINTF_FLAG_ALT | P_MY_PRINTF_FLAG_ZERO_PAD |
    P_MY_PRINTF_FLAG_LEFT_ADJUST | P_MY_PRINTF_FLAG_SIGN_BLANK |
    P_MY_PRINTF_FLAG_PLACE_SIGN | P_MY_PRINTF_FLAG_GROUP_DIGITS |
    P_MY_PRINTF_FLAG_ALT_DIGITS;

    cr_assert_eq(p_my_printf_get_flags(&str), flags);
    cr_assert_str_eq(str, "after");
}

Test(p_my_printf_get_flags, same_flag)
{
    char const *str = "----%s";
    int flags = P_MY_PRINTF_FLAG_LEFT_ADJUST;

    cr_assert_eq(p_my_printf_get_flags(&str), flags);
    cr_assert_str_eq(str, "%s");
}
