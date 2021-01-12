/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_lpad & p_my_printf_rpad functions
*/

#include <criterion/criterion.h>
#include "libmy/printf.h"

Test(p_my_printf_lpad, no_field_width)
{
    p_my_printf_conv_t conv = {
        .flags = 0,
        .field_width = 0,
    };
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_lpad(&stream, &conv, 10, ' '), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 0);
}

Test(p_my_printf_lpad, wrong_flags)
{
    p_my_printf_conv_t conv = {
        .flags = P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH |
        P_MY_PRINTF_FLAG_LEFT_ADJUST,
        .field_width = 15,
    };
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_lpad(&stream, &conv, 10, '.'), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 0);
}

Test(p_my_printf_lpad, small_field_width)
{
    p_my_printf_conv_t conv = {
        .flags = P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH,
        .field_width = 2,
    };
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_lpad(&stream, &conv, 10, '?'), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 0);
}

Test(p_my_printf_lpad, io_error)
{
    p_my_printf_conv_t conv = {
        .flags = P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH,
        .field_width = 15,
    };
    char buf[2];
    my_iostream_t stream;

    my_finit_output_memory(buf, 2, &stream);
    cr_assert_neq(p_my_printf_lpad(&stream, &conv, 10, '!'), 0);
}

Test(p_my_printf_lpad, big_field_width)
{
    p_my_printf_conv_t conv = {
        .flags = P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH,
        .field_width = 15,
    };
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_lpad(&stream, &conv, 10, '!'), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 5);
    buf[written] = '\0';
    cr_assert_str_eq(buf, "!!!!!");
}

Test(p_my_printf_rpad, no_field_width)
{
    p_my_printf_conv_t conv = {
        .flags = 0,
        .field_width = 0,
    };
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_rpad(&stream, &conv, 10, ' '), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 0);
}

Test(p_my_printf_rpad, wrong_flags)
{
    p_my_printf_conv_t conv = {
        .flags = P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH,
        .field_width = 15,
    };
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_rpad(&stream, &conv, 10, '.'), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 0);
}

Test(p_my_printf_rpad, small_field_width)
{
    p_my_printf_conv_t conv = {
        .flags = P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH,
        .field_width = 2,
    };
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_rpad(&stream, &conv, 10, '?'), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 0);
}

Test(p_my_printf_rpad, io_error)
{
    p_my_printf_conv_t conv = {
        .flags = P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH |
        P_MY_PRINTF_FLAG_LEFT_ADJUST,
        .field_width = 15,
    };
    char buf[2];
    my_iostream_t stream;

    my_finit_output_memory(buf, 2, &stream);
    cr_assert_neq(p_my_printf_rpad(&stream, &conv, 10, '!'), 0);
}

Test(p_my_printf_rpad, big_field_width)
{
    p_my_printf_conv_t conv = {
        .flags = P_MY_PRINTF_FLAG_HAS_FIELD_WIDTH |
        P_MY_PRINTF_FLAG_LEFT_ADJUST,
        .field_width = 15,
    };
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_rpad(&stream, &conv, 10, '!'), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 5);
    buf[written] = '\0';
    cr_assert_str_eq(buf, "!!!!!");
}

Test(p_my_printf_zpad, no_zeros)
{
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_zpad(&stream, 0), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 0);
}

Test(p_my_printf_zpad, io_error)
{
    char buf[2];
    my_iostream_t stream;

    my_finit_output_memory(buf, 2, &stream);
    cr_assert_neq(p_my_printf_zpad(&stream, 10), 0);
}

Test(p_my_printf_zpad, normal)
{
    char buf[64];
    my_iostream_t stream;
    size_t written = 42;

    my_finit_output_memory(buf, 64, &stream);
    cr_assert_eq(p_my_printf_zpad(&stream, 5), 0);
    my_fget_buffer(&written, &stream);
    cr_assert_eq(written, 5);
    buf[written] = '\0';
    cr_assert_str_eq(buf, "00000");
}
