/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Parses the next command
*/

#include <sys/types.h>

#include <dirent.h>
#include <libmy/ascii/ascii.h>
#include <libmy/printf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"
#include "command.h"
#include "util.h"

static char *sh_find_in_dir(char const *to_find, char const *dir_name)
{
    DIR *dir = opendir(dir_name);
    char *result = NULL;

    if (!dir)
        return NULL;
    for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir)) {
        if (my_strcmp(to_find, entry->d_name) == 0) {
            result = sh_create_file_path(
                my_strlen(dir_name), dir_name, entry->d_name);
            break;
        }
    }
    closedir(dir);
    return result;
}

static char *sh_find_executable(sh_ctx_t *ctx, char const *to_find)
{
    char *found = NULL;

    for (size_t i = 0; i < ctx->path.length; ++i) {
        found =
            sh_find_in_dir(to_find, MY_VEC_GET_ELEM(char *, &ctx->path, i));
        if (found)
            break;
    }
    return found;
}

static int sh_command_resolve_external(
    sh_ctx_t *ctx, sh_command_t *command, char const *name)
{
    bool is_path = my_strchr(name, '/') != NULL;

    command->external.path =
        is_path ? my_strdup(name) : sh_find_executable(ctx, name);
    if (!command->external.path) {
        my_fprintf(MY_STDERR, "%s: Command not found.\n", name);
        my_flush_stderr();
        return 1;
    } else if (access(command->external.path, X_OK) < 0) {
        perror(name);
        if (!is_path)
            free((char *)command->external.path);
        return 1;
    }
    command->command_type = SH_COMMAND_EXTERNAL;
    return 0;
}

int sh_command_resolve(sh_ctx_t *ctx, sh_command_t *command)
{
    sh_builtin_t const *builtin;
    char const *name;

    if (command->base.args.length == 0)
        return 1;
    name = MY_VEC_GET(char const *, &command->base.args, 0);
    builtin = sh_get_builtin(name);
    if (builtin != NULL) {
        command->command_type = SH_COMMAND_BUILTIN;
        command->builtin.builtin = builtin;
        return 0;
    }
    return sh_command_resolve_external(ctx, command, name);
}