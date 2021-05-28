/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Variable handling
*/

#ifndef __SHELL_VARIABLES_H__
#define __SHELL_VARIABLES_H__

#include "context.h"
#include "util.h"

typedef struct sh_var_value {
    sh_lstr_t inner;
    bool read_only;
} sh_var_value_t;

/// Validates a variable name.
///
/// A valid variable name matches the regex [a-zA-Z_][a-zA-Z_0-9]*
///
/// @param name The variable name.
/// @param name_len The number of characters in @c name.
///
/// @returns @c SH_OK if @c name is a valid variable name, or an error code
/// otherwise.
sh_error_t sh_check_var_name(char const *name, size_t name_len);

/// Expands the first variable encountered in <tt>*str</tt> from
/// <tt>*offset</tt>.
///
/// @param ctx The shell context.
/// @param[in, out] str A pointer to the string to expand, may be reallocated.
/// @param[in, out] offset A pointer to the starting position in the string,
/// set to the position of the first character after the end of the varable's
/// value, or the position of the null-terminator if no variable is found.
/// @param[out] name The name of the variable set regardless of errors or set
/// to @c NULL if no variable is found.
///
/// @returns @c SH_OK if expansion failed, @c SH_OUT_OF_MEMORY,
/// @c SH_UNDEFINED_VAR.
sh_error_t sh_expand_var(
    sh_ctx_t *ctx, char **str, size_t *offset, char const **name);

/// Expands all variables in <tt>*str</tt>, losing all variable value
/// position information in the process.
///
/// Do use this function if you require knowledge of where the variable are
/// expanded for argument inserting purposes.
sh_error_t sh_expand_vars(sh_ctx_t *ctx, char **str);

#endif // !defined(__SHELL_VARIABLES_H__)
