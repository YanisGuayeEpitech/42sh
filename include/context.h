/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** The shell context
*/

#ifndef __SHELL_CONTEXT_H__
#define __SHELL_CONTEXT_H__

#include <libmy/collections.h>

#include "definition.h"

typedef struct {
    /// A vector of the environment entries.
    my_vec_t env;
    /// A vector of the entries from the PATH environment variable.
    my_vec_t path;
    /// A vector of sh_command_t
    my_vec_t pipeline;
    /// Is stdin a tty?
    int is_tty;
    /// The exit code of the previous program.
    int exit_code;
    /// The previous working directory, initialized to @c NULL.
    char *old_pwd;
    /// Exit value of exit builtins
    int exit_builtins;
} sh_ctx_t;

/// Initializes the shell's context
///
/// @param envp A NULL-terminared array of strings.
///
/// @returns 0 if successful.
int sh_ctx_init(sh_ctx_t *ctx, char **envp);

/// Frees the contents of the shell context.
///
/// @param ctx The shell context.
void sh_ctx_drop(sh_ctx_t *ctx);

/// Reads the path environment variable
///
/// @param ctx The shell context.>
void sh_ctx_reset_path(sh_ctx_t *ctx);

#endif // !defined(__SHELL_CONTEXT_H__)
