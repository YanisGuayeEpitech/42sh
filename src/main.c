/*
** EPITECH PROJECT, 2021
** bs-minishell1
** File description:
** the main file
*/

#include <sys/types.h>

#include <libmy/ascii.h>
#include <libmy/io.h>
#include <libmy/printf.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static void report_status(int status)
{
    my_putstr("Program terminated.\nStatus: ");
    if (WIFEXITED(status)) {
        my_putstr("OK\n");
    } else if (WIFSIGNALED(status)) {
        my_putendl(strsignal(WTERMSIG(status)));
    } else {
        my_putstr("NOT EXITED!\n");
    }
}

static size_t count_args(char const **args)
{
    size_t argc = 0;

    while (args[argc])
        ++argc;
    return argc;
}

static int exec_args(char const **args, char *envp[])
{
    size_t argc = count_args(args);
    pid_t child_pid;
    int status;

    if (argc == 0)
        return 0;
    my_printf("Program name: %s\nNb args: %zu\nPID: %d\n", args[0], argc - 1,
        getpid());
    child_pid = fork();
    if (child_pid < 0) {
        my_putstr_fd(STDERR_FILENO, "couldn't fork process\n");
        return 84;
    } else if (child_pid == 0) {
        execve(args[0], (char *const *)args, envp);
    }
    my_printf("Child PID: %d\n", child_pid);
    waitpid(child_pid, &status, 0);
    report_status(status);
    return 0;
}

int main(int argc, char *argv[], char *envp[])
{
    char **args;
    int ret;

    if (argc != 2) {
        my_putstr_fd(STDERR_FILENO, "wrong number of arguments\n");
        return 84;
    }
    args = my_str_to_word_array(argv[1]);
    if (!args) {
        my_putstr_fd(STDERR_FILENO, "failed to allocate argument array\n");
        return 84;
    }
    ret = exec_args((char const **)args, envp);
    for (size_t i = 0; args[i]; ++i)
        free(args[i]);
    free(args);
    return ret;
}