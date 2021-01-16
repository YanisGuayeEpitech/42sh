/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Prints errors
*/

#include <libmy/io.h>
#include "shell.h"

static char const *ERROR_MESSAGES[SH_ERROR_MAX] = {
    [SH_OK] = "no error",
    [SH_EXPRESSION_SYNTAX] = "Expression Syntax",
    [SH_BAD_NUMBER] = "Badly formed number",
    [SH_BAD_VAR_START] = "Variable name must begin with a letter",
    [SH_BAD_VAR_CHARS] = "Variable name must contain alphanumeric characters",
};

char const *sh_strerror(sh_error_t code)
{
    if (code < SH_OK || code >= SH_ERROR_MAX)
        return "Unknown error";
    return ERROR_MESSAGES[code];
}

sh_error_t sh_perror(char const *prefix, sh_error_t code)
{
    if (code == SH_OK)
        return code;
    if (prefix && *prefix) {
        my_eputs(prefix);
        my_eputs(": ");
    }
    my_eputs(sh_strerror(code));
    my_eputs(".\n");
    return code;
}
