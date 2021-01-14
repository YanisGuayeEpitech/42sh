/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Shell context functions
*/

#include <libmy/ascii.h>
#include <libmy/io.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

static void sh_free_env_entry(void *ptr)
{
    free(*(char **)ptr);
}

static int sh_copy_env(sh_ctx_t *ctx, char **envp)
{
    size_t env_size = 0;
    char *entry = NULL;

    env_size = 0;
    while (envp[env_size])
        ++env_size;
    if (my_vec_init_capacity(&ctx->env, env_size + 1, sizeof(*envp)))
        return 84;
    for (size_t i = 0; i < env_size; ++i) {
        entry = my_strdup(envp[i]);
        if (!entry) {
            my_vec_free(&ctx->env, &sh_free_env_entry);
            return 84;
        }
        my_vec_push(&ctx->env, &entry);
    }
    entry = NULL;
    my_vec_push(&ctx->env, &entry);
    return 0;
}

int sh_ctx_init(sh_ctx_t *ctx, char **envp)
{
    if (sh_copy_env(ctx, envp))
        return 84;
    ctx->path_index = SIZE_MAX;
    for (size_t i = 0; i < ctx->env.length - 1; ++i) {
        if (my_strncmp(MY_VEC_GET_ELEM(char *, &ctx->env, i), "PATH=", 5)
            == 0) {
            ctx->path_index = i;
            break;
        }
    }
    ctx->is_tty = isatty(MY_STDOUT->unix_stream.fd);
    return 0;
}

void sh_ctx_drop(sh_ctx_t *ctx)
{
    my_vec_free(&ctx->env, &sh_free_env_entry);
}