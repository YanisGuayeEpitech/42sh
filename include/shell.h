/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** The main header file$
*/

#ifndef __SHELL_H__
#define __SHELL_H__

#include <libmy/collections.h>

#define IO_BUF_SIZE (1024)

typedef struct {
    my_vec_t env;
    int is_tty;
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

#endif // !defined(__SHELL_H__)
