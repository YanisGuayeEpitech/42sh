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

int sh_ctx_init(sh_ctx_t *ctx, char **envp)
{
    size_t env_size = 0;
    char *entry = NULL;

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
    ctx->is_tty = isatty(MY_STDOUT->unix_stream.fd);
    return 0;
}

void sh_ctx_drop(sh_ctx_t *ctx)
{
    my_vec_free(&ctx->env, &sh_free_env_entry);
}