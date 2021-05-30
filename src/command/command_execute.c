/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Executes the given command
*/

#include <assert.h>
#include <libmy/io/iostream.h>
#include <stdio.h>

#include "command.h"
#include "shell.h"
#include "util.h"
#include "variables.h"

int sh_command_execute(
    sh_ctx_t *ctx, sh_command_t *command, sh_command_t *next_command)
{
    assert(ctx != NULL && command != NULL);
    if (!sh_command_open_redirects(ctx, command, next_command))
        return 0;
    if ((command->command_type != SH_COMMAND_NOT_FOUND
            && !sh_command_globbing(ctx, command))
        || !sh_command_expand_vars(ctx, command))
        return 0;
    switch (command->command_type) {
        case SH_COMMAND_EXTERNAL:
            return sh_execute_external(ctx, &command->external);
        case SH_COMMAND_BUILTIN:
            return sh_execute_builtin(ctx, &command->builtin);
        case SH_COMMAND_NOT_FOUND:
            ctx->exit_code = 1;
            my_eputs(MY_VEC_GET(char *, &command->base.args, 0));
            my_eputs(": Command not found.\n");
            my_flush_stderr();
            return 0;
        default: return sh_rerror(NULL, SH_OUT_OF_MEMORY, -1);
    }
}
