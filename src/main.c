/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** The entry point of the program
*/

#include <libmy/io.h>
#include <stdlib.h>
#include "shell.h"

static int init_stdio(void)
{
    if (my_init_stdout(malloc(IO_BUF_SIZE), IO_BUF_SIZE, &free))
        return 84;
    if (my_init_stderr(malloc(IO_BUF_SIZE), IO_BUF_SIZE, &free)) {
        my_free_stdout();
        return 84;
    }
    if (my_init_stdin(malloc(IO_BUF_SIZE), IO_BUF_SIZE, &free)) {
        my_free_stdout();
        my_free_stderr();
        return 84;
    }
    return 0;
}

static void free_stdio(void)
{
    my_free_stdout();
    my_free_stderr();
    my_free_stdin();
}

int main(int argc, char *argv[], char *envp[])
{
    sh_ctx_t ctx;

    (void)argc;
    (void)argv;
    if (init_stdio())
        return 84;
    if (sh_ctx_init(&ctx, envp)) {
        free_stdio();
        return 84;
    }
    free_stdio();
    return 0;
}