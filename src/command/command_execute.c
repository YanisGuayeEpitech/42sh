/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes the given command
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtin.h"
#include "command.h"
#include "shell.h"

static void sh_run_child(sh_ctx_t *ctx, char const *path, char const *argv[])
{
    execve(path, (char *const *)argv, ctx->env.data);
    perror(argv[0]);
    exit(1);
}

static int sh_exec_external(sh_ctx_t *ctx, char const *path,
    char const *argv[], sh_pipe_pos_t pipe_pos)
{
    pid_t child_pid;
    int status;
    int old_pipe_fd[2];
    int ret = sh_external_pipe_setup(ctx, pipe_pos, old_pipe_fd);

    if (ret != 0)
        return ret;
    child_pid = fork();
    if (child_pid < 0) {
        return 1;
    } else if (child_pid == 0) {
        sh_external_pipe_dup(ctx, pipe_pos, old_pipe_fd);
        sh_run_child(ctx, path, argv);
    }
    ret = sh_external_pipe_close(ctx, pipe_pos, old_pipe_fd);
    if (pipe_pos == SH_PIPE_END)
        do {
            waitpid(child_pid, &status, 0);
        } while (sh_handle_status(ctx, status));
    return ret;
}

int sh_command_execute(sh_ctx_t *ctx, sh_command_t const *command,
    sh_command_t const *next_command)
{
    assert(ctx != NULL);
    assert(command != NULL);
    switch (command->command_type) {
        case SH_COMMAND_BUILTIN:
            return sh_exec_builtin(command->builtin.builtin, ctx,
                command->base.args.length - 1, command->base.args.data);
        case SH_COMMAND_EXTERNAL:
            return sh_exec_external(ctx, command->external.path,
                command->base.args.data, command->base.pipe_pos);
        default: return sh_rerror(NULL, SH_OUT_OF_MEMORY, -1);
    }
    (void)next_command;
}
