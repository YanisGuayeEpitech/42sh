/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** The setenv builtin
*/

#include <libmy/ascii.h>
#include <libmy/io.h>
#include "builtin.h"
#include "shell.h"

int sh_builtin_setenv(
    sh_ctx_t *ctx, int *should_exit, size_t argc, char const *argv[])
{
    sh_error_t code;

    if (argc == 1)
        return sh_builtin_env(ctx, should_exit, 1, argv);
    if (argc > 3)
        return sh_rerror(argv[0], SH_TOO_MANY_ARGS, 1);
    code = sh_check_var_name(argv[1], my_strlen(argv[1]));
    if (code != SH_OK)
        return sh_rerror(argv[0], code, 1);
    sh_env_set(ctx, argv[1], argc == 3 ? argv[2] : "");
    return 0;
}
