/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Starts the shell
*/

#include <libmy/io.h>
#include <libmy/printf.h>
#include <stdlib.h>
#include "shell.h"

static ssize_t sh_get_input(sh_ctx_t *ctx, char **line, size_t *alloc_size)
{
    sh_print(ctx, "$> ");
    return my_getline(line, alloc_size, MY_STDIN);
}

void sh_start(sh_ctx_t *ctx)
{
    char *line = NULL;
    size_t alloc_size = 0;
    ssize_t line_size;

    (void)ctx;
    line_size = sh_get_input(ctx, &line, &alloc_size);
    while (line_size > 0) {
        sh_print(ctx, "-> ");
        sh_print(ctx, line);
        line_size = sh_get_input(ctx, &line, &alloc_size);
    }
    sh_print(ctx, "exit\n");
    free(line);
}