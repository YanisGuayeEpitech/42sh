/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Parsing functions
*/

#include <libmy/ascii.h>
#include "shell.h"

sh_error_t sh_parse_int(char const *str, int *result)
{
    int negate = 0;

    if (!*str)
        return SH_BAD_NUMBER;
    if (*str == '-') {
        if (*(++str) == '-')
            return SH_BAD_NUMBER;
        negate = 1;
    }
    while (*str) {
        if (!my_isdigit(*str))
            return SH_BAD_NUMBER;
        *result = *result * 10 + (int)(*str - '0');
        ++str;
    }
    if (negate)
        *result = -*result;
    return 0;
}

sh_error_t sh_check_var_name(char const *name, size_t name_len)
{
    if (!name || name_len == 0 || !(my_isalpha(*name) || *name == '_'))
        return SH_BAD_VAR_START;
    for (size_t i = 1; i < name_len; ++i)
        if (!(my_isalnum(name[i]) || name[i] == '_'))
            return SH_BAD_VAR_CHARS;
    return SH_OK;
}
