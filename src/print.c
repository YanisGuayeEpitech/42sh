/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Prints message if it's a tty
*/

#include <libmy/io.h>
#include "shell.h"

void sh_print(sh_ctx_t *ctx, char const *msg)
{
    if (ctx->is_tty) {
        my_puts(msg);
        my_flush_stdout();
    }
}

void sh_print_prompt(sh_ctx_t *ctx)
{
    sh_print(ctx, "$> ");
}
