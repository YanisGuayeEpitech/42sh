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

const sh_builtin_t BUILTINS[] = {
    {"bindkey", &sh_builtin_bindkey},
    {"builtins", &sh_builtin_builtins},
    {"cd", &sh_builtin_cd},
    {"env", &sh_builtin_env},
    {"exit", &sh_builtin_exit},
    {"repeat", &sh_builtin_repeat},
    {"set", &sh_builtin_set},
    {"setenv", &sh_builtin_setenv},
    {"unsetenv", &sh_builtin_unsetenv},
};
const size_t BUILTIN_COUNT = sizeof(BUILTINS) / sizeof(sh_builtin_t);

static const my_array_t BUILTINS_ARRAY = {
    .data = (void *)BUILTINS,
    .length = BUILTIN_COUNT,
    .elem_size = sizeof(sh_builtin_t),
};

static int sh_builtin_cmp(char *to_find, sh_builtin_t *builtin)
{
    return my_strcmp(to_find, builtin->name);
}

sh_builtin_t const *sh_get_builtin(char const *name)
{
    size_t pos = my_binary_search(&BUILTINS_ARRAY, name, &sh_builtin_cmp);

    if (pos == SIZE_MAX)
        return NULL;
    return &BUILTINS[pos];
}
