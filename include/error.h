/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Error handling utilities
*/

#ifndef __SHELL_ERROR_H__
#define __SHELL_ERROR_H__

#include "definition.h"

typedef enum {
    SH_OK = 0,
    SH_EXPRESSION_SYNTAX,
    SH_BAD_NUMBER,
    SH_BAD_VAR_START,
    SH_BAD_VAR_CHARS,
    SH_TOO_MANY_ARGS,
    SH_TOO_FEW_ARGS,
    SH_CD_NO_HOME_DIR,
    SH_CD_HOME_DIR,
    SH_OUT_OF_MEMORY,
    SH_ERROR_MAX,
} sh_error_t;

/// Retrurns a string corresponding to the given error code.
///
/// @param code The error code.
///
/// @returns The error string, or "Unknown error" if <tt>code < SH_OK</tt> or
/// <tt>code >= SH_ERROR_MAX</tt>.
char const *sh_strerror(sh_error_t code);

/// Prints the given error code to the standard error output.
///
/// Does nothing if @c code is @c SH_OK.
///
/// @param prefix If not null or empty, prefix is printed followed by a color
/// and a blank.
/// @param code The error code.
///
/// @returns The @c code argument.
sh_error_t sh_perror(char const *prefix, sh_error_t code);

/// Calls @ref sh_perror then returns the value of @c ret.
///
/// @param prefix If not null, prefix is printed followed by a color
/// and a blank.
/// @param code The error code.
///
/// @returns The @c ret argument.
SH_INLINE int sh_rerror(char const *prefix, sh_error_t code, int ret)
{
    sh_perror(prefix, code);
    return ret;
}

int sh_perror_errno(char const *prefix);

SH_INLINE int sh_rerror_errno(char const *prefix, int ret)
{
    sh_perror_errno(prefix);
    return ret;
}

#endif // !defined(__SHELL_ERROR_H__)
