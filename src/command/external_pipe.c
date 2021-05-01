/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Handle pipes to external commands
*/

#include <unistd.h>

#include "command.h"

static int sclose(int *fd)
{
    int ret;

    if (*fd == -1)
        return 0;
    ret = close(*fd);
    *fd = -1;
    return ret;
}

int sh_external_pipe_setup(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2])
{
    switch (pipe_pos) {
        case SH_PIPE_BEGIN: return pipe(ctx->pipe_fd) == -1;
        case SH_PIPE_MIDDLE:
            old_pipe_fd[0] = ctx->pipe_fd[0];
            old_pipe_fd[1] = ctx->pipe_fd[1];
            return pipe(ctx->pipe_fd) == -1;
        default: return 0;
    }
}

int sh_external_pipe_dup(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2])
{
    switch (pipe_pos) {
        case SH_PIPE_BEGIN:
            return dup2(ctx->pipe_fd[1], STDOUT_FILENO) == -1
                || sclose(ctx->pipe_fd);
        case SH_PIPE_MIDDLE:
            return dup2(old_pipe_fd[0], STDIN_FILENO) == -1
                || dup2(ctx->pipe_fd[1], STDOUT_FILENO) == -1
                || sclose(old_pipe_fd + 1) || sclose(ctx->pipe_fd);
        case SH_PIPE_END:
            if (ctx->pipe_fd[0] == -1)
                return 0;
            return dup2(ctx->pipe_fd[0], STDIN_FILENO) == -1
                || sclose(ctx->pipe_fd + 1);
        default: __builtin_unreachable();
    }
}

int sh_external_pipe_close(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2])
{
    switch (pipe_pos) {
        case SH_PIPE_MIDDLE:
            return sclose(old_pipe_fd) || sclose(old_pipe_fd + 1);
        case SH_PIPE_END:
            return sclose(ctx->pipe_fd) || sclose(ctx->pipe_fd + 1);
        default: return 0;
    }
}
