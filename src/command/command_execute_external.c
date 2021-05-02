/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes the given external command
*/

#include <assert.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "command.h"
#include "shell.h"

static void sh_run_child(sh_ctx_t *ctx, char const *path, char const *argv[])
{
    execve(path, (char *const *)argv, ctx->env.data);
    sh_perror_errno(argv[0]);
    exit(1);
}

static int sh_execute_external_impl(sh_ctx_t *ctx, char const *path,
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

int sh_execute_external(sh_ctx_t *ctx, char const *path, char const *argv[],
    sh_pipe_pos_t pipe_pos)
{
    if (access(path, X_OK) < 0) {
        ctx->exit_code = 1;
        return sh_rerror_errno(path, 0);
    }
    return sh_execute_external_impl(ctx, path, argv, pipe_pos);
}
