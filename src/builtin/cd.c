/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** The cd builtin
*/

#include <libmy/io.h>
#include "builtin.h"

int sh_builtin_cd(sh_ctx_t *ctx, int *should_exit, size_t argc, char *argv[])
{
    my_flush_stdout();
    for (size_t i = 0; i < argc; ++i)
        my_puts_endl(argv[i]);
    my_flush_stdout();
    (void)ctx;
    (void)should_exit;
    return 0;
}