/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Environment variable functions
*/

#include <libmy/ascii.h>
#include <libmy/memory.h>
#include <stdlib.h>
#include "shell.h"

char **sh_env_get_entry(sh_ctx_t *ctx, char const *key, size_t key_len)
{
    size_t len = ctx->env.length - 1;

    for (size_t i = 0; i < len; ++i) {
        char **entry = my_vec_get(&ctx->env, i);

        if (my_strncmp(key, *entry, key_len) == 0)
            return entry;
    }
    return NULL;
}

void sh_env_set(sh_ctx_t *ctx, char const *key, char const *value)
{
    size_t key_len = my_strlen(key);
    size_t value_len = my_strlen(value);
    char *new_entry = malloc(sizeof(*new_entry) * (key_len + value_len + 2));
    char **old_entry = sh_env_get_entry(ctx, key, key_len);

    if (!new_entry)
        return;
    my_memcpy(new_entry, key, key_len);
    new_entry[key_len] = '=';
    my_memcpy(new_entry + key_len + 1, value, value_len);
    new_entry[key_len + value_len + 1] = '\0';
    if (old_entry) {
        free(*old_entry);
        *old_entry = new_entry;
    } else {
        my_vec_push(&ctx->env, &old_entry);
        *((char **)my_vec_get(&ctx->env, ctx->env.length - 2)) = new_entry;
    }
}

int sh_env_remove(sh_ctx_t *ctx, char const *key)
{
    char **entry = sh_env_get_entry(ctx, key, my_strlen(key));
    char **new_env;
    size_t index;

    if (!entry)
        return 0;
    index = (size_t)(entry - (char **)ctx->env.data);
    new_env = malloc(sizeof(*new_env) * (ctx->env.length - 1));
    if (!new_env)
        return 0;
    free(*entry);
    for (size_t i = 0; i < index; ++i)
        new_env[i] = MY_VEC_GET_ELEM(char *, &ctx->env, i);
    for (size_t i = index + 1; i < ctx->env.length; ++i)
        new_env[i - 1] = MY_VEC_GET_ELEM(char *, &ctx->env, i);
    free(ctx->env.data);
    ctx->env.data = new_env;
    ctx->env.capacity = ctx->env.length - 1;
    --ctx->env.length;
    return 1;
}
