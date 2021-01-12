/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the p_my_printf_fill_args function
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include "libmy/printf.h"

static const p_my_printf_arg_type_t POINTER_ARGS[10] = {
    P_MY_PRINTF_ARG_STRING,
    P_MY_PRINTF_ARG_POINTER,
    P_MY_PRINTF_ARG_PTR_SCHAR,
    P_MY_PRINTF_ARG_PTR_SHORT,
    P_MY_PRINTF_ARG_PTR_INT,
    P_MY_PRINTF_ARG_PTR_LONG,
    P_MY_PRINTF_ARG_PTR_LONG_LONG,
    P_MY_PRINTF_ARG_PTR_SIZE_T,
    P_MY_PRINTF_ARG_PTR_INTMAX_T,
    P_MY_PRINTF_ARG_PTR_PTRDIFF_T
};

static const p_my_printf_arg_type_t INT_ARGS[8] = {
    P_MY_PRINTF_ARG_SBYTE,
    P_MY_PRINTF_ARG_SHORT,
    P_MY_PRINTF_ARG_INT,
    P_MY_PRINTF_ARG_LONG,
    P_MY_PRINTF_ARG_LONG_LONG,
    P_MY_PRINTF_ARG_SSIZE_T,
    P_MY_PRINTF_ARG_INTMAX_T,
    P_MY_PRINTF_ARG_PTRDIFF_T,
};

static const p_my_printf_arg_type_t UINT_ARGS[8] = {
    P_MY_PRINTF_ARG_BYTE,
    P_MY_PRINTF_ARG_USHORT,
    P_MY_PRINTF_ARG_UINT,
    P_MY_PRINTF_ARG_ULONG,
    P_MY_PRINTF_ARG_ULONG_LONG,
    P_MY_PRINTF_ARG_SIZE_T,
    P_MY_PRINTF_ARG_UINTMAX_T,
    P_MY_PRINTF_ARG_UPTRDIFF_T,
};

static const p_my_printf_arg_type_t MISC_ARGS[3] = {
    P_MY_PRINTF_ARG_CHAR,
    P_MY_PRINTF_ARG_DOUBLE,
    P_MY_PRINTF_ARG_LONG_DOUBLE,
};

static const char *STRING_ARG = "test";
static const char CHAR_ARG = '?';
static const double DOUBLE_ARG = -69.420;
static const long double LONG_DOUBLE_ARG = 6591.3453;

static const signed char SBYTE_ARG = -42;
static const short SHORT_ARG = -0x342;
static const int INT_ARG = -0xf001245;
static const long LONG_ARG = -0x367899801234567;
static const long long LONG_LONG_ARG = -0x892369801345627;
static const ssize_t SIZE_T_ARG = -0x376926969726970;
static const intmax_t INTMAX_T_ARG = -0x972384562897013;
static const ptrdiff_t PTRDIFF_T_ARG = -587103;

static const unsigned char BYTE_ARG = 42;
static const unsigned short USHORT_ARG = 0x2342;
static const unsigned int UINT_ARG = 0xff001245;
static const unsigned long ULONG_ARG = 0x2367899801234567;
static const unsigned long long ULONG_LONG_ARG = 0x7892369801345627;
static const size_t SSIZE_T_ARG = 0x2376926969726970;
static const uintmax_t UINTMAX_T_ARG = 0x6972384562897013;
static const ptrdiff_t UPTRDIFF_T_ARG = 587103;

static p_my_printf_arg_type_t *fill_args(size_t count, p_my_printf_arg_t args[],
p_my_printf_arg_type_t const types[], ...)
{
    va_list va_args;
    p_my_printf_arg_type_t *copy;

    va_start(va_args, types);
    copy = malloc(sizeof(*copy) * count);
    memcpy(copy, types, sizeof(*copy) * count);
    p_my_printf_fill_args(count, args, copy, va_args);
    va_end(va_args);
    return copy;
}

Test(p_my_printf_fill_args, pointers)
{
    p_my_printf_arg_t args[10];
    p_my_printf_arg_type_t *types = fill_args(10, args, POINTER_ARGS,
    STRING_ARG, STRING_ARG, &CHAR_ARG, &SHORT_ARG, &INT_ARG, &LONG_ARG,
    &LONG_LONG_ARG, &SIZE_T_ARG, &INTMAX_T_ARG, &PTRDIFF_T_ARG);

    cr_assert_str_eq(args[0].string_arg, "test");
    cr_assert_eq(args[1].pointer_arg, STRING_ARG);
    cr_assert_eq(args[2].schar_ptr_arg, &CHAR_ARG);
    cr_assert_eq(args[3].short_ptr_arg, &SHORT_ARG);
    cr_assert_eq(args[4].int_ptr_arg, &INT_ARG);
    cr_assert_eq(args[5].long_ptr_arg, &LONG_ARG);
    cr_assert_eq(args[6].long_long_ptr_arg, &LONG_LONG_ARG);
    cr_assert_eq(args[7].size_t_ptr_arg, &SIZE_T_ARG);
    cr_assert_eq(args[8].intmax_t_ptr_arg, &INTMAX_T_ARG);
    cr_assert_eq(args[9].ptrdiff_t_ptr_arg, &PTRDIFF_T_ARG);
    for (size_t i = 0; i < 10; ++i)
        cr_assert_eq(types[i], POINTER_ARGS[i]);
    free(types);
}

Test(p_my_printf_fill_args, signed_integers)
{
    p_my_printf_arg_t args[8];
    p_my_printf_arg_type_t *types = fill_args(8, args, INT_ARGS,
    SBYTE_ARG, SHORT_ARG, INT_ARG, LONG_ARG, LONG_LONG_ARG, SSIZE_T_ARG,
    INTMAX_T_ARG, PTRDIFF_T_ARG);

    cr_assert_eq(args[0].sint_arg, SBYTE_ARG);
    cr_assert_eq(args[1].sint_arg, SHORT_ARG);
    cr_assert_eq(args[2].sint_arg, INT_ARG);
    cr_assert_eq(args[3].sint_arg, LONG_ARG);
    cr_assert_eq(args[4].sint_arg, LONG_LONG_ARG);
    cr_assert_eq(args[5].sint_arg, SSIZE_T_ARG);
    cr_assert_eq(args[6].sint_arg, INTMAX_T_ARG);
    cr_assert_eq(args[7].sint_arg, PTRDIFF_T_ARG);
    for (size_t i = 0; i < 8; ++i)
        cr_assert_eq(types[i], P_MY_PRINTF_ARG_INTMAX_T);
    free(types);
}

Test(p_my_printf_fill_args, unsigned_integers)
{
    p_my_printf_arg_t args[8];
    p_my_printf_arg_type_t *types = fill_args(8, args, UINT_ARGS,
    BYTE_ARG, USHORT_ARG, UINT_ARG, ULONG_ARG, ULONG_LONG_ARG, SIZE_T_ARG,
    UINTMAX_T_ARG, UPTRDIFF_T_ARG);

    cr_assert_eq(args[0].uint_arg, BYTE_ARG);
    cr_assert_eq(args[1].uint_arg, USHORT_ARG);
    cr_assert_eq(args[2].uint_arg, UINT_ARG);
    cr_assert_eq(args[3].uint_arg, ULONG_ARG);
    cr_assert_eq(args[4].uint_arg, ULONG_LONG_ARG);
    cr_assert_eq(args[5].uint_arg, SIZE_T_ARG);
    cr_assert_eq(args[6].uint_arg, UINTMAX_T_ARG);
    cr_assert_eq(args[7].uint_arg, (uintmax_t)UPTRDIFF_T_ARG);
    for (size_t i = 0; i < 8; ++i)
        cr_assert_eq(types[i], P_MY_PRINTF_ARG_UINTMAX_T);
    free(types);
}

Test(p_my_printf_fill_args, misc)
{
    p_my_printf_arg_t args[3];
    p_my_printf_arg_type_t *types = fill_args(3, args, MISC_ARGS,
    CHAR_ARG, DOUBLE_ARG, LONG_DOUBLE_ARG);

    cr_assert_eq(args[0].char_arg, CHAR_ARG);
    cr_assert_eq(args[1].double_arg, DOUBLE_ARG);
    cr_assert_eq(args[2].long_double_arg, LONG_DOUBLE_ARG);
    for (size_t i = 0; i < 3; ++i)
        cr_assert_eq(types[i], MISC_ARGS[i]);
    free(types);
}
