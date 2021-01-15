/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Handle builtin commands
*/

#include "builtin.h"
#include <libmy/ascii.h>
#include <libmy/memory.h>
#include <stdint.h>

static const sh_builtin_t BUILTINS_DATA[] = {{"env", &sh_builtin_env}};

static const size_t BUILTINS_COUNT =
    sizeof(BUILTINS_DATA) / sizeof(sh_builtin_t);
static const my_array_t BUILTINS = {.data = (void *)BUILTINS_DATA,
    .length = BUILTINS_COUNT,
    .elem_size = sizeof(sh_builtin_t)};

static int sh_builtin_cmp(char *to_find, sh_builtin_t *builtin)
{
    return my_strcmp(to_find, builtin->name);
}

sh_builtin_t const *sh_get_builtin(char const *name)
{
    size_t pos = my_binary_search(&BUILTINS, name, &sh_builtin_cmp);

    if (pos == SIZE_MAX)
        return NULL;
    return &BUILTINS_DATA[pos];
}

int sh_exec_builtin(
    sh_builtin_t const *builtin, sh_ctx_t *ctx, size_t argc, char *argv[])
{
    int should_exit = 0;

    (*builtin->run)(ctx, &should_exit, argc, argv);
    if (should_exit)
        return -1;
    return 0;
}
