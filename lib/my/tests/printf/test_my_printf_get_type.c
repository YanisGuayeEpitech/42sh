/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_get_type function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

static p_my_printf_arg_type_t get_type(char const *str)
{
    p_my_printf_length_t len = p_my_printf_get_len_modifier(&str);
    p_my_printf_specifier_t spec = p_my_printf_get_conv_specifier(&str);

    return p_my_printf_get_type(len, spec);
}

Test(p_my_printf_get_type, invalid_combinations)
{
    cr_assert_eq(get_type(""), P_MY_PRINTF_ARG_INT);
    cr_assert_eq(get_type("z"), P_MY_PRINTF_ARG_INT);
    cr_assert_eq(get_type("Ld"), P_MY_PRINTF_ARG_INT);
    cr_assert_eq(get_type("Lc"), P_MY_PRINTF_ARG_CHAR);
}

Test(p_my_printf_get_type, signed_integers)
{
    cr_assert_eq(get_type("d"), P_MY_PRINTF_ARG_INT);
    cr_assert_eq(get_type("hhd"), P_MY_PRINTF_ARG_SBYTE);
    cr_assert_eq(get_type("hd"), P_MY_PRINTF_ARG_SHORT);
    cr_assert_eq(get_type("ld"), P_MY_PRINTF_ARG_LONG);
    cr_assert_eq(get_type("lld"), P_MY_PRINTF_ARG_LONG_LONG);
    cr_assert_eq(get_type("jd"), P_MY_PRINTF_ARG_INTMAX_T);
    cr_assert_eq(get_type("zd"), P_MY_PRINTF_ARG_SSIZE_T);
    cr_assert_eq(get_type("td"), P_MY_PRINTF_ARG_PTRDIFF_T);
}

Test(p_my_printf_get_type, unsigned_integers)
{
    cr_assert_eq(get_type("u"), P_MY_PRINTF_ARG_UINT);
    cr_assert_eq(get_type("hhu"), P_MY_PRINTF_ARG_BYTE);
    cr_assert_eq(get_type("hu"), P_MY_PRINTF_ARG_USHORT);
    cr_assert_eq(get_type("lu"), P_MY_PRINTF_ARG_ULONG);
    cr_assert_eq(get_type("llu"), P_MY_PRINTF_ARG_ULONG_LONG);
    cr_assert_eq(get_type("ju"), P_MY_PRINTF_ARG_UINTMAX_T);
    cr_assert_eq(get_type("zu"), P_MY_PRINTF_ARG_SIZE_T);
    cr_assert_eq(get_type("tu"), P_MY_PRINTF_ARG_UPTRDIFF_T);
}

Test(p_my_printf_get_type, octal_integers)
{
    cr_assert_eq(get_type("o"), P_MY_PRINTF_ARG_UINT);
    cr_assert_eq(get_type("hho"), P_MY_PRINTF_ARG_BYTE);
    cr_assert_eq(get_type("ho"), P_MY_PRINTF_ARG_USHORT);
    cr_assert_eq(get_type("lo"), P_MY_PRINTF_ARG_ULONG);
    cr_assert_eq(get_type("llo"), P_MY_PRINTF_ARG_ULONG_LONG);
    cr_assert_eq(get_type("jo"), P_MY_PRINTF_ARG_UINTMAX_T);
    cr_assert_eq(get_type("zo"), P_MY_PRINTF_ARG_SIZE_T);
    cr_assert_eq(get_type("to"), P_MY_PRINTF_ARG_UPTRDIFF_T);
}

Test(p_my_printf_get_type, lower_hex_integers)
{
    cr_assert_eq(get_type("x"), P_MY_PRINTF_ARG_UINT);
    cr_assert_eq(get_type("hhx"), P_MY_PRINTF_ARG_BYTE);
    cr_assert_eq(get_type("hx"), P_MY_PRINTF_ARG_USHORT);
    cr_assert_eq(get_type("lx"), P_MY_PRINTF_ARG_ULONG);
    cr_assert_eq(get_type("llx"), P_MY_PRINTF_ARG_ULONG_LONG);
    cr_assert_eq(get_type("jx"), P_MY_PRINTF_ARG_UINTMAX_T);
    cr_assert_eq(get_type("zx"), P_MY_PRINTF_ARG_SIZE_T);
    cr_assert_eq(get_type("tx"), P_MY_PRINTF_ARG_UPTRDIFF_T);
}

Test(p_my_printf_get_type, upper_hex_integers)
{
    cr_assert_eq(get_type("X"), P_MY_PRINTF_ARG_UINT);
    cr_assert_eq(get_type("hhX"), P_MY_PRINTF_ARG_BYTE);
    cr_assert_eq(get_type("hX"), P_MY_PRINTF_ARG_USHORT);
    cr_assert_eq(get_type("lX"), P_MY_PRINTF_ARG_ULONG);
    cr_assert_eq(get_type("llX"), P_MY_PRINTF_ARG_ULONG_LONG);
    cr_assert_eq(get_type("jX"), P_MY_PRINTF_ARG_UINTMAX_T);
    cr_assert_eq(get_type("zX"), P_MY_PRINTF_ARG_SIZE_T);
    cr_assert_eq(get_type("tX"), P_MY_PRINTF_ARG_UPTRDIFF_T);
}

Test(p_my_printf_get_type, lower_floats)
{
    cr_assert_eq(get_type("f"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hhf"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hf"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("lf"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("llf"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("zf"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("jf"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("tf"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("Lf"), P_MY_PRINTF_ARG_LONG_DOUBLE);
}

Test(p_my_printf_get_type, upper_floats)
{
    cr_assert_eq(get_type("F"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hhF"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hF"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("lF"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("llF"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("zF"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("jF"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("tF"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("LF"), P_MY_PRINTF_ARG_LONG_DOUBLE);
}

Test(p_my_printf_get_type, lower_float_exponents)
{
    cr_assert_eq(get_type("e"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hhe"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("he"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("le"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("lle"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("ze"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("je"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("te"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("Le"), P_MY_PRINTF_ARG_LONG_DOUBLE);
}

Test(p_my_printf_get_type, upper_float_exponents)
{
    cr_assert_eq(get_type("E"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hhE"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hE"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("lE"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("llE"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("zE"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("jE"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("tE"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("LE"), P_MY_PRINTF_ARG_LONG_DOUBLE);
}

Test(p_my_printf_get_type, lower_float_scientific)
{
    cr_assert_eq(get_type("g"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hhg"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hg"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("lg"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("llg"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("zg"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("jg"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("tg"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("Lg"), P_MY_PRINTF_ARG_LONG_DOUBLE);
}

Test(p_my_printf_get_type, upper_float_scientific)
{
    cr_assert_eq(get_type("G"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hhG"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hG"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("lG"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("llG"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("zG"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("jG"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("tG"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("LG"), P_MY_PRINTF_ARG_LONG_DOUBLE);
}

Test(p_my_printf_get_type, lower_float_hex)
{
    cr_assert_eq(get_type("a"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hha"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("ha"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("la"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("lla"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("za"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("ja"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("ta"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("La"), P_MY_PRINTF_ARG_LONG_DOUBLE);
}

Test(p_my_printf_get_type, upper_float_hex)
{
    cr_assert_eq(get_type("A"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hhA"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("hA"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("lA"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("llA"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("zA"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("jA"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("tA"), P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(get_type("LA"), P_MY_PRINTF_ARG_LONG_DOUBLE);
}

Test(p_my_printf_get_type, chars)
{
    cr_assert_eq(get_type("c"), P_MY_PRINTF_ARG_CHAR);
    cr_assert_eq(get_type("hhc"), P_MY_PRINTF_ARG_CHAR);
    cr_assert_eq(get_type("hc"), P_MY_PRINTF_ARG_CHAR);
    cr_assert_eq(get_type("lc"), P_MY_PRINTF_ARG_CHAR);
    cr_assert_eq(get_type("llc"), P_MY_PRINTF_ARG_CHAR);
    cr_assert_eq(get_type("jc"), P_MY_PRINTF_ARG_CHAR);
    cr_assert_eq(get_type("zc"), P_MY_PRINTF_ARG_CHAR);
    cr_assert_eq(get_type("tc"), P_MY_PRINTF_ARG_CHAR);
}

Test(p_my_printf_get_type, strings)
{
    cr_assert_eq(get_type("s"), P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(get_type("hhs"), P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(get_type("hs"), P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(get_type("ls"), P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(get_type("lls"), P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(get_type("js"), P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(get_type("zs"), P_MY_PRINTF_ARG_STRING);
    cr_assert_eq(get_type("ts"), P_MY_PRINTF_ARG_STRING);
}

Test(p_my_printf_get_type, pointers)
{
    cr_assert_eq(get_type("p"), P_MY_PRINTF_ARG_POINTER);
    cr_assert_eq(get_type("hhp"), P_MY_PRINTF_ARG_POINTER);
    cr_assert_eq(get_type("hp"), P_MY_PRINTF_ARG_POINTER);
    cr_assert_eq(get_type("lp"), P_MY_PRINTF_ARG_POINTER);
    cr_assert_eq(get_type("llp"), P_MY_PRINTF_ARG_POINTER);
    cr_assert_eq(get_type("jp"), P_MY_PRINTF_ARG_POINTER);
    cr_assert_eq(get_type("zp"), P_MY_PRINTF_ARG_POINTER);
    cr_assert_eq(get_type("tp"), P_MY_PRINTF_ARG_POINTER);
}

Test(p_my_printf_get_type, count_pointers)
{
    cr_assert_eq(get_type("n"), P_MY_PRINTF_ARG_PTR_INT);
    cr_assert_eq(get_type("hhn"), P_MY_PRINTF_ARG_PTR_SCHAR);
    cr_assert_eq(get_type("hn"), P_MY_PRINTF_ARG_PTR_SHORT);
    cr_assert_eq(get_type("ln"), P_MY_PRINTF_ARG_PTR_LONG);
    cr_assert_eq(get_type("lln"), P_MY_PRINTF_ARG_PTR_LONG_LONG);
    cr_assert_eq(get_type("jn"), P_MY_PRINTF_ARG_PTR_INTMAX_T);
    cr_assert_eq(get_type("zn"), P_MY_PRINTF_ARG_PTR_SIZE_T);
    cr_assert_eq(get_type("tn"), P_MY_PRINTF_ARG_PTR_PTRDIFF_T);
}
