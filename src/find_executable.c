/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Finds an executable in path
*/

#include <sys/types.h>

#include <dirent.h>
#include <libmy/ascii.h>
#include "shell.h"

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

char *sh_find_executable(sh_ctx_t *ctx, char const *to_find)
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
