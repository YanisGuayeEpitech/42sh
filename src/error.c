/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Prints errors
*/

#include <errno.h>
#include <libmy/io.h>
#include <stdio.h>
#include "shell.h"

static char const *ERROR_MESSAGES[SH_ERROR_MAX] = {
    [SH_OK] = "no error",
    [SH_EXPRESSION_SYNTAX] = "Expression Syntax",
    [SH_BAD_NUMBER] = "Badly formed number",
    [SH_BAD_VAR_START] = "Variable name must begin with a letter",
    [SH_BAD_VAR_CHARS] = "Variable name must contain alphanumeric characters",
    [SH_TOO_MANY_ARGS] = "Too many arguments",
    [SH_TOO_FEW_ARGS] = "Too few arguments",
    [SH_CD_NO_HOME_DIR] = "No home directory",
    [SH_CD_HOME_DIR] = "Can't change to home directory",
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
    if (prefix) {
        my_eputs(prefix);
        my_eputs(": ");
    }
    my_eputs(sh_strerror(code));
    my_eputs(".\n");
    return code;
}

int sh_perror_errno(char const *prefix)
{
    if (prefix) {
        my_eputs(prefix);
        my_eputs(": ");
    }
    my_flush_stderr();
    perror(NULL);
    return errno;
}
