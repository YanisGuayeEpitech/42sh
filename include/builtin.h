/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** The shell's context
*/

#ifndef __SHELL_BUILTIN_H__
#define __SHELL_BUILTIN_H__

#include "context.h"

typedef struct {
    char const *name;
    int (*run)(sh_ctx_t *, int *, size_t, char **);
} sh_builtin_t;

/// Fetches a builtin command by name.
///
/// @param name The name of the command.
///
/// @return The builtin, or @c NULL if not found.
sh_builtin_t const *sh_get_builtin(char const *name);

int sh_exec_builtin(
    sh_builtin_t const *builtin, sh_ctx_t *ctx, size_t argc, char *argv[]);

int sh_builtin_env(sh_ctx_t *ctx, int *should_exit, size_t argc, char *argv[]);
int sh_builtin_exit(
    sh_ctx_t *ctx, int *should_exit, size_t argc, char *argv[]);
int sh_builtin_setenv(
    sh_ctx_t *ctx, int *should_exit, size_t argc, char *argv[]);

#endif // !defined(__SHELL_BUILTIN_H__)
