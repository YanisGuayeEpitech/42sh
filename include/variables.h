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

#endif // !defined(__SHELL_VARIABLES_H__)
