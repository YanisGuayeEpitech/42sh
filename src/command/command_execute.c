/*
** EPITECH PROJECT, 2021
** 42sh
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
#include "util.h"

static int sh_command_open_redirects(
    sh_ctx_t *ctx, sh_command_t *c1, sh_command_t *c2)
{
    if (c1->base.input != NULL) {
        c1->base.pipe_in[0] = open(c1->base.input, SH_INPUT_FLAGS);
        if (c1->base.pipe_in[0] < 0) {
            ctx->exit_code = 1;
            return sh_rerror_errno(c1->base.input, 1);
        }
    }
    if (c1->base.output != NULL) {
        c1->base.pipe_out[1] =
            open(c1->base.output, SH_OUTPUT_FLAGS(c1), SH_OUTPUT_MODE);
        if (c1->base.pipe_out[1] < 0) {
            ctx->exit_code = 1;
            return sh_rerror_errno(c1->base.output, 1);
        }
    } else if (c2 != NULL) {
        pipe(c1->base.pipe_out);
        c2->base.pipe_in[0] = c1->base.pipe_out[0];
        c2->base.pipe_in[1] = c1->base.pipe_out[1];
    }
    return 0;
}

int sh_command_execute(
    sh_ctx_t *ctx, sh_command_t *command, sh_command_t *next_command)
{
    assert(ctx != NULL);
    assert(command != NULL);
    if (sh_command_open_redirects(ctx, command, next_command))
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
