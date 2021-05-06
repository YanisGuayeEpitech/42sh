/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Starts the shell
*/

#include <libmy/io/iostream.h>

#include "shell.h"

void sh_start(sh_ctx_t *ctx)
{
    sh_token_stream_t stream;

    sh_token_stream_init(&stream);
    sh_print_prompt(ctx);
    while (sh_token_stream_next(&stream, SIZE_MAX) >= 0) {
        if (my_feof(MY_STDIN)
            || sh_execute(ctx, stream.tokens.length, stream.tokens.data) < 0)
            break;
        my_fflush(MY_STDERR);
        sh_print_prompt(ctx);
    }
    my_fflush(MY_STDERR);
    sh_print(ctx, "exit\n");
    sh_token_stream_drop(&stream);
}
