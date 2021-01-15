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
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "builtin.h"
#include "shell.h"

static int sh_handle_status(int status)
{
    if (WIFEXITED(status)) {
        return 0;
    } else if (WIFSIGNALED(status)) {
        my_eputs(strsignal(WTERMSIG(status)));
        if (WCOREDUMP(status))
            my_eputs(" (core dumped)");
        my_eputc('\n');
        my_flush_stderr();
        return 0;
    }
    return 1;
}

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
    do {
        waitpid(child_pid, &status, 0);
    } while (sh_handle_status(status));
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
    sh_builtin_t const *builtin;
    int ret = 0;

    if (!args)
        return 0;
    while (args[args_count])
        ++args_count;
    builtin = args_count > 0 ? sh_get_builtin(args[0]) : NULL;
    if (builtin)
        ret = sh_exec_builtin(builtin, ctx, args_count, args);
    else if (args_count > 0)
        ret = sh_exec_from_path(ctx, args);
    for (size_t i = 0; args[i]; ++i)
        free(args[i]);
    free(args);
    return ret;
}
