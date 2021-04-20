/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes user input
*/

#include <sys/types.h>

#include <libmy/ascii.h>
#include <libmy/printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "builtin.h"
#include "shell.h"

static void sh_run_child(sh_ctx_t *ctx, char const *path, char const *argv[])
{
    execve(path, (char *const *)argv, ctx->env.data);
    perror(argv[0]);
    exit(1);
}

static int sh_exec_args(sh_ctx_t *ctx, char const *path, char const *argv[],
    sh_pipe_pos_t pipe_pos)
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

static int sh_exec_from_path(
    sh_ctx_t *ctx, char const *argv[], sh_pipe_pos_t pipe_pos)
{
    int is_path = my_strchr(argv[0], '/') != NULL;
    char const *path = is_path ? argv[0] : sh_find_executable(ctx, argv[0]);
    int ret;

    if (!path) {
        my_fprintf(MY_STDERR, "%s: Command not found.\n", argv[0]);
        my_flush_stderr();
        return 1;
    } else if (access(path, X_OK) < 0) {
        perror(argv[0]);
        if (!is_path)
            free((char *)path);
        return 1;
    }
    ret = sh_exec_args(ctx, path, argv, pipe_pos);
    if (!is_path)
        free((char *)path);
    return ret;
}

int sh_exec(
    sh_ctx_t *ctx, size_t argc, char const *argv[], sh_pipe_pos_t pipe_pos)
{
    sh_builtin_t const *builtin;
    int ret = 0;

    builtin = sh_get_builtin(argv[0]);
    if (builtin)
        ret = sh_exec_builtin(builtin, ctx, argc, argv);
    else
        ret = sh_exec_from_path(ctx, argv, pipe_pos);
    return ret;
}
