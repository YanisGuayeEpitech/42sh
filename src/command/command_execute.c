/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes the given command
*/

#include <assert.h>
#include <fcntl.h>
#include <libmy/printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "command.h"
#include "shell.h"

static int sh_command_open_redirects(sh_ctx_t *ctx, sh_command_t *command)
{
    int input_fd = -1;
    int output_fd = -1;

    if (command->base.input != NULL) {
        input_fd = open(command->base.input, O_RDONLY);
        if (input_fd < 0) {
            ctx->exit_code = 1;
            return sh_rerror_errno(command->base.input, 0);
        }
    }
    if (command->base.output != NULL) {
        output_fd = open(command->base.output, O_WRONLY | O_CREAT, 0661);
        if (output_fd < 0) {
            ctx->exit_code = 1;
            return sh_rerror_errno(command->base.output, 0);
        }
    }
}

int sh_command_execute(
    sh_ctx_t *ctx, sh_command_t *command, sh_command_t const *next_command)
{
    assert(ctx != NULL && command != NULL);
    // if (command->base.input != NULL && access(command->base.input, R_OK)) {
    //    ctx->exit_code = 1;
    //    return sh_rerror_errno(command->base.input, 0);
    //}
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
