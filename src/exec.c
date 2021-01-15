/*
** EPITECH PROJECT, 2021
** minishell1
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
#include "shell.h"

static int sh_exec_args(sh_ctx_t *ctx, char const *path, char *const *argv)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid < 0) {
        return 0;
    } else if (child_pid == 0
        && execve(path, (char *const *)argv, ctx->env.data) < 0) {
        perror(argv[0]);
        return -1;
    }
    waitpid(child_pid, &status, 0);
    return 0;
}

static int sh_exec_from_path(sh_ctx_t *ctx, char *const *argv)
{
    int is_path = my_strchr(argv[0], '/') != NULL;
    char const *path = is_path ? argv[0] : sh_find_executable(ctx, argv[0]);
    int ret;

    if (!path) {
        my_fprintf(MY_STDERR, "%s: Command not found.\n", argv[0]);
        my_flush_stderr();
        return 0;
    } else if (access(path, X_OK) < 0) {
        perror(argv[0]);
        if (!is_path)
            free((char *)path);
        return 0;
    }
    ret = sh_exec_args(ctx, path, argv);
    if (!is_path)
        free((char *)path);
    return ret;
}

int sh_exec(sh_ctx_t *ctx, char const *line)
{
    char **args = my_str_to_word_array(line);
    size_t args_count = 0;
    int ret = 0;

    if (!args)
        return 0;
    while (args[args_count])
        ++args_count;
    if (args_count > 0)
        ret = sh_exec_from_path(ctx, args);
    for (size_t i = 0; args[i]; ++i)
        free(args[i]);
    free(args);
    return ret;
}
