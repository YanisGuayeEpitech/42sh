/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** The env builtin
*/

#include <libmy/io.h>
#include "builtin.h"

int sh_builtin_env(sh_ctx_t *ctx, int *should_exit, size_t argc, char *argv[])
{
    size_t env_len = ctx->env.length - 1;

    for (size_t i = 0; i < env_len; ++i)
        my_puts_endl(MY_VEC_GET_ELEM(char *, &ctx->env, i));
    my_flush_stdout();
    (void)should_exit;
    (void)argc;
    (void)argv;
    return 0;
}