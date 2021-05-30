/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Fetch builtin commands
*/

#include <libmy/ascii.h>
#include <libmy/io.h>
#include <libmy/memory.h>
#include <stdint.h>
#include "builtin.h"

static const sh_builtin_t BUILTINS_DATA[] = {
    {"bindkey", &sh_builtin_bindkey},
    {"cd", &sh_builtin_cd},
    {"env", &sh_builtin_env},
    {"exit", &sh_builtin_exit},
    {"repeat", &sh_builtin_repeat},
    {"set", &sh_builtin_set},
    {"setenv", &sh_builtin_setenv},
    {"source", &sh_builtin_source},
    {"unsetenv", &sh_builtin_unsetenv},
};

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
