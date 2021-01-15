/*
** EPITECH PROJECT, 2021
** minishell1
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
