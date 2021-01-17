/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Starts the shell
*/

#include <libmy/io.h>
#include <stdlib.h>
#include "shell.h"

void sh_start(sh_ctx_t *ctx)
{
    char *line = NULL;
    size_t alloc_size = 0;
    ssize_t line_size;

    (void)ctx;
    sh_print_prompt(ctx);
    line_size = my_getline(&line, &alloc_size, MY_STDIN);
    while (line_size > 0) {
        if (sh_exec(ctx, line) < 0)
            break;
        sh_print_prompt(ctx);
        line_size = my_getline(&line, &alloc_size, MY_STDIN);
    }
    sh_print(ctx, "exit\n");
    free(line);
}
