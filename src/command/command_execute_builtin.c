/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes the given builtin command
*/

#include <libmy/io.h>

#include "builtin.h"
#include "command.h"
#include "shell.h"

int sh_execute_builtin(sh_ctx_t *ctx, sh_builtin_command_t *command)
{
    int should_exit = 0;

    ctx->exit_code = (*command->builtin->run)(
        ctx, &should_exit, command->base.args.length, command->base.args.data);
    my_flush_stdout();
    my_flush_stderr();
    if (should_exit)
        return -1;
    return 0;
}
