/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes the given builtin command
*/

#include <libmy/io.h>

#include "builtin.h"
#include "shell.h"

int sh_execute_builtin(sh_builtin_t const *builtin, sh_ctx_t *ctx, size_t argc,
    char const *argv[])
{
    int should_exit = 0;

    ctx->exit_code = (*builtin->run)(ctx, &should_exit, argc, argv);
    my_flush_stdout();
    my_flush_stderr();
    if (should_exit)
        return -1;
    return 0;
}
