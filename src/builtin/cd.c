/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** The cd builtin
*/

#include <libmy/printf.h>
#include <stdio.h>
#include <unistd.h>
#include "builtin.h"
#include "shell.h"

static sh_dirs_options_t sh_cd_get_option(
    char opt, sh_dirs_options_t options, int *is_valid)
{
    switch (opt) {
        case 'p': return options | SH_DIRS_PRINT;
        case 'l': return options | SH_DIRS_LONG;
        case 'n': return options | SH_DIRS_WRAP;
        case 'v': return options | SH_DIRS_FULL;
        default: {
            *is_valid = 0;
            return options;
        }
    }
}

static int sh_cd_parse_params(
    char const *name, char const *arg, sh_dirs_options_t *options, size_t *pos)
{
    int is_valid = 1;

    if (arg[0] != '-')
        return 3;
    if (arg[1] == '\0')
        return 2;
    *pos += 1;
    if (arg[1] == '-')
        return 3;
    for (size_t i = 1; arg[i]; ++i) {
        *options = sh_cd_get_option(arg[i], *options, &is_valid);
        if (!is_valid) {
            my_printf("Usage: %s [-plvn][-|<dir>].\n", name);
            return 1;
        }
    }
    return 0;
}

static int sh_cd_home(sh_ctx_t *ctx, char const *name)
{
    char **home = sh_env_get_entry(ctx, "HOME", 4);

    if (!home)
        return sh_rerror(name, SH_CD_NO_HOME_DIR, 1);
    if (chdir(*home + 5) < 0)
        return sh_rerror(name, SH_CD_HOME_DIR, 1);
    return 0;
}

static int sh_cd_dir(sh_ctx_t *ctx, char const *path)
{
    char **oldpwd;

    if (path == NULL) {
        oldpwd = sh_env_get_entry(ctx, "OLDPWD", 6);
        if (oldpwd)
            path = *oldpwd + 7;
    }
    path = path ? path : "";
    if (chdir(path) < 0)
        return sh_rerror_errno(path, 1);
    (void)ctx;
    return 0;
}

int sh_builtin_cd(
    sh_ctx_t *ctx, int *should_exit, size_t argc, char const *argv[])
{
    sh_dirs_options_t options = 0;
    size_t pos = 1;
    int ret = 3;

    while (pos < argc) {
        ret = sh_cd_parse_params(argv[0], argv[pos], &options, &pos);
        if (ret == 1)
            return 1;
        if (ret == 2 || ret == 3)
            break;
    }
    if (pos >= argc)
        ret = sh_cd_home(ctx, argv[0]);
    else
        ret = sh_cd_dir(ctx, ret == 2 ? NULL : argv[pos]);
    if (ret == 0)
        sh_dirs_run(ctx, options);
    (void)should_exit;
    return ret;
}
