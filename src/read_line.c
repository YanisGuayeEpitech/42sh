/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Reads the next line from stdin
*/

#include <libmy/io.h>
#include "shell.h"

ssize_t sh_read_line(sh_ctx_t *ctx)
{
    ssize_t bytes_read = my_getline(
        (char **)&ctx->line_buf.data, &ctx->line_buf.capacity, MY_STDIN);

    ctx->line_buf.length = bytes_read < 1 ? 0 : (size_t)bytes_read - 1;
    return bytes_read;
}
