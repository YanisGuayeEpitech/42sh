/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_parse_conversion function
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

static p_my_printf_conv_t parse_conv(char const **src,
p_my_printf_arg_t const args[], p_my_printf_arg_type_t const types[],
size_t *pos)
{
    return p_my_printf_parse_conversion(src, args, types, pos);
}

Test(p_my_printf_parse_conversion, empty_fmt_string)
{
    char const *src = "";
    size_t pos = 0;
    p_my_printf_conv_t conv = parse_conv(&src, NULL, NULL, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_NONE);
    cr_assert_str_eq(src, "");
    cr_assert_eq(pos, 0);
}

Test(p_my_printf_parse_conversion, invalid_conversion)
{
    char const *src = "Wd";
    size_t pos = 0;
    p_my_printf_conv_t conv = parse_conv(&src, NULL, NULL, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_NONE);
    cr_assert_str_eq(src, "Wd");
    cr_assert_eq(pos, 0);
}

Test(p_my_printf_parse_conversion, unfinished_conversion)
{
    char const *src = "#-+ll";
    size_t pos = 0;
    p_my_printf_conv_t conv = parse_conv(&src, NULL, NULL, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_NONE);
    cr_assert_str_eq(src, "#-+ll");
    cr_assert_eq(pos, 0);
}

Test(p_my_printf_parse_conversion, simple_conversion)
{
    char const *src = "dend";
    size_t pos = 0;
    p_my_printf_arg_t arg = { .sint_arg = 42 };
    p_my_printf_arg_type_t type = P_MY_PRINTF_ARG_INTMAX_T;
    p_my_printf_conv_t conv = parse_conv(&src, &arg, &type, &pos);

    cr_assert_eq(pos, 1);
    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_SIGNED);
    cr_assert_str_eq(src, "end");
    cr_assert_eq(pos, 1);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_INTMAX_T);
    cr_assert_eq(conv.value.sint_arg, 42);
    cr_assert_eq(conv.flags, 0);
    cr_assert_eq(conv.field_width, 0);
    cr_assert_eq(conv.precision, 0);
}

Test(p_my_printf_parse_conversion, simple_conversion_with_flags)
{
    char const *src = "#Is%zu";
    size_t pos = 0;
    p_my_printf_arg_t arg = { .string_arg = "yeet" };
    p_my_printf_arg_type_t type = P_MY_PRINTF_ARG_STRING;
    p_my_printf_conv_t conv = parse_conv(&src, &arg, &type, &pos);


    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_STRING);
    cr_assert_str_eq(src, "%zu");
    cr_assert_eq(pos, 1);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_STRING);
    cr_assert_str_eq(conv.value.string_arg, "yeet");
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_ALT |
    P_MY_PRINTF_FLAG_ALT_DIGITS);
    cr_assert_eq(conv.field_width, 0);
    cr_assert_eq(conv.precision, 0);
}

Test(p_my_printf_parse_conversion, simple_conversion_with_field_width)
{
    char const *src = "016zx";
    size_t pos = 0;
    p_my_printf_arg_t arg = { .sint_arg = 1234 };
    p_my_printf_arg_type_t type = P_MY_PRINTF_ARG_INTMAX_T;
    p_my_printf_conv_t conv = parse_conv(&src, &arg, &type, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_LOWER_HEXADECIMAL);
    cr_assert_str_eq(src, "");
    cr_assert_eq(pos, 1);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_INTMAX_T);
    cr_assert_eq(conv.value.sint_arg, 1234);
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_ZERO_PAD |
    P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH);
    cr_assert_eq(conv.field_width, 16);
    cr_assert_eq(conv.precision, 0);
}

Test(p_my_printf_parse_conversion, simple_conversion_with_zero_precision)
{
    char const *src = ".jd";
    size_t pos = 0;
    p_my_printf_arg_t arg = { .sint_arg = -67890 };
    p_my_printf_arg_type_t type = P_MY_PRINTF_ARG_INTMAX_T;
    p_my_printf_conv_t conv = parse_conv(&src, &arg, &type, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_SIGNED);
    cr_assert_str_eq(src, "");
    cr_assert_eq(pos, 1);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_INTMAX_T);
    cr_assert_eq(conv.value.sint_arg, -67890);
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_HAS_PRECISION);
    cr_assert_eq(conv.field_width, 0);
    cr_assert_eq(conv.precision, 0);
}

Test(p_my_printf_parse_conversion, simple_conversion_with_precision)
{
    char const *src = "+.4le!";
    size_t pos = 0;
    p_my_printf_arg_t arg = { .long_double_arg = 42.12345 };
    p_my_printf_arg_type_t type = P_MY_PRINTF_ARG_LONG_DOUBLE;
    p_my_printf_conv_t conv = parse_conv(&src, &arg, &type, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_LOWER_FLOAT_EXPONENT);
    cr_assert_str_eq(src, "!");
    cr_assert_eq(pos, 1);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_LONG_DOUBLE);
    cr_assert_eq(conv.value.long_double_arg, 42.12345);
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_PLACE_SIGN |
    P_MY_PRINTF_FLAG_HAS_PRECISION);
    cr_assert_eq(conv.field_width, 0);
    cr_assert_eq(conv.precision, 4);
}

Test(p_my_printf_parse_conversion, positional_conversion)
{
    char const *src = "2$hho?";
    size_t pos = 0;
    p_my_printf_arg_t args[] = {
        { .string_arg = "yeet" },
        { .sint_arg = 42 }
    };
    p_my_printf_arg_type_t types[] = {
        P_MY_PRINTF_ARG_STRING,
        P_MY_PRINTF_ARG_INTMAX_T
    };
    p_my_printf_conv_t conv = parse_conv(&src, args, types, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_OCTAL);
    cr_assert_str_eq(src, "?");
    cr_assert_eq(pos, 0);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_INTMAX_T);
    cr_assert_eq(conv.value.sint_arg, 42);
    cr_assert_eq(conv.flags, 0);
    cr_assert_eq(conv.field_width, 0);
    cr_assert_eq(conv.precision, 0);
}

Test(p_my_printf_parse_conversion, parametized_field_width)
{
    char const *src = "*A?!";
    size_t pos = 0;
    p_my_printf_arg_t args[] = {
        { .sint_arg = 13 },
        { .double_arg = -4.2 }
    };
    p_my_printf_arg_type_t types[] = {
        P_MY_PRINTF_ARG_INTMAX_T,
        P_MY_PRINTF_ARG_DOUBLE
    };
    p_my_printf_conv_t conv = parse_conv(&src, args, types, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_UPPER_FLOAT_HEXADECIMAL);
    cr_assert_str_eq(src, "?!");
    cr_assert_eq(pos, 2);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(conv.value.double_arg, -4.2);
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH);
    cr_assert_eq(conv.field_width, 13);
    cr_assert_eq(conv.precision, 0);
}

Test(p_my_printf_parse_conversion, negative_field_width)
{
    char const *src = "*g?!";
    size_t pos = 0;
    p_my_printf_arg_t args[] = {
        { .sint_arg = -13 },
        { .double_arg = 687.131 }
    };
    p_my_printf_arg_type_t types[] = {
        P_MY_PRINTF_ARG_INTMAX_T,
        P_MY_PRINTF_ARG_DOUBLE
    };
    p_my_printf_conv_t conv = parse_conv(&src, args, types, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_LOWER_FLOAT_SCIENTIFIC);
    cr_assert_str_eq(src, "?!");
    cr_assert_eq(pos, 2);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(conv.value.double_arg, 687.131);
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH |
    P_MY_PRINTF_FLAG_LEFT_ADJUST);
    cr_assert_eq(conv.field_width, 13);
}

Test(p_my_printf_parse_conversion, positional_field_width)
{
    char const *src = "*2$A?!";
    size_t pos = 0;
    p_my_printf_arg_t args[] = {
        { .double_arg = -2.4 },
        { .sint_arg = 20 }
    };
    p_my_printf_arg_type_t types[] = {
        P_MY_PRINTF_ARG_DOUBLE,
        P_MY_PRINTF_ARG_INTMAX_T
    };
    p_my_printf_conv_t conv = parse_conv(&src, args, types, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_UPPER_FLOAT_HEXADECIMAL);
    cr_assert_str_eq(src, "?!");
    cr_assert_eq(pos, 1);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(conv.value.double_arg, -2.4);
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH);
    cr_assert_eq(conv.field_width, 20);
    cr_assert_eq(conv.precision, 0);
}

Test(p_my_printf_parse_conversion, parametized_precision)
{
    char const *src = ".*A?!";
    size_t pos = 0;
    p_my_printf_arg_t args[] = {
        { .sint_arg = 13 },
        { .double_arg = -4.2 }
    };
    p_my_printf_arg_type_t types[] = {
        P_MY_PRINTF_ARG_INTMAX_T,
        P_MY_PRINTF_ARG_DOUBLE
    };
    p_my_printf_conv_t conv = parse_conv(&src, args, types, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_UPPER_FLOAT_HEXADECIMAL);
    cr_assert_str_eq(src, "?!");
    cr_assert_eq(pos, 2);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(conv.value.double_arg, -4.2);
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_HAS_PRECISION);
    cr_assert_eq(conv.field_width, 0);
    cr_assert_eq(conv.precision, 13);
}

Test(p_my_printf_parse_conversion, negative_precision)
{
    char const *src = ".*g?!";
    size_t pos = 0;
    p_my_printf_arg_t args[] = {
        { .sint_arg = -13 },
        { .double_arg = 687.131 }
    };
    p_my_printf_arg_type_t types[] = {
        P_MY_PRINTF_ARG_INTMAX_T,
        P_MY_PRINTF_ARG_DOUBLE
    };
    p_my_printf_conv_t conv = parse_conv(&src, args, types, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_LOWER_FLOAT_SCIENTIFIC);
    cr_assert_str_eq(src, "?!");
    cr_assert_eq(pos, 2);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(conv.value.double_arg, 687.131);
    cr_assert_eq(conv.flags, 0);
    cr_assert_eq(conv.precision, 0);
    cr_assert_eq(conv.field_width, 0);
}

Test(p_my_printf_parse_conversion, positional_precision)
{
    char const *src = ".*2$A?!";
    size_t pos = 0;
    p_my_printf_arg_t args[] = {
        { .double_arg = -2.4 },
        { .sint_arg = 20 }
    };
    p_my_printf_arg_type_t types[] = {
        P_MY_PRINTF_ARG_DOUBLE,
        P_MY_PRINTF_ARG_INTMAX_T
    };
    p_my_printf_conv_t conv = parse_conv(&src, args, types, &pos);

    cr_assert_eq(conv.specifier, P_MY_PRINTF_SPEC_UPPER_FLOAT_HEXADECIMAL);
    cr_assert_str_eq(src, "?!");
    cr_assert_eq(pos, 1);
    cr_assert_eq(conv.type, P_MY_PRINTF_ARG_DOUBLE);
    cr_assert_eq(conv.value.double_arg, -2.4);
    cr_assert_eq(conv.flags, P_MY_PRINTF_FLAG_HAS_PRECISION);
    cr_assert_eq(conv.field_width, 0);
    cr_assert_eq(conv.precision, 20);
}
