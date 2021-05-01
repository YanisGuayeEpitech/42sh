/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes the given command
*/

#include <assert.h>
#include <libmy/printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "command.h"
#include "shell.h"

int sh_command_execute(sh_ctx_t *ctx, sh_command_t const *command,
    sh_command_t const *next_command)
{
    assert(ctx != NULL);
    assert(command != NULL);
    switch (command->command_type) {
        case SH_COMMAND_EXTERNAL:
            return sh_execute_external(ctx, command->external.path,
                command->base.args.data, command->base.pipe_pos);
        case SH_COMMAND_BUILTIN:
            return sh_execute_builtin(command->builtin.builtin, ctx,
                command->base.args.length - 1, command->base.args.data);
        case SH_COMMAND_NOT_FOUND:
            my_eputs(MY_VEC_GET(char *, &command->base.args, 0));
            my_eputs(": Command not found.\n");
            my_flush_stderr();
            return 0;
        default: return sh_rerror(NULL, SH_OUT_OF_MEMORY, -1);
    }
    (void)next_command;
}
