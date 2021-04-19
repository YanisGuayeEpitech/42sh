/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Shell context functions
*/

#include <libmy/ascii.h>
#include <libmy/io.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

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
            my_vec_free(&ctx->env, &sh_free_entry);
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
    my_vec_init(&ctx->path, sizeof(char *));
    sh_ctx_reset_path(ctx);
    ctx->is_tty = isatty(MY_STDIN->unix_stream.fd);
    ctx->exit_code = 0;
    my_vec_init(&ctx->line_buf, sizeof(char));
    ctx->old_pwd = NULL;
    ctx->pipe_fd[0] = -1;
    ctx->pipe_fd[1] = -1;
    return 0;
}

void sh_ctx_drop(sh_ctx_t *ctx)
{
    my_vec_free(&ctx->env, &sh_free_entry);
    my_vec_free(&ctx->path, &sh_free_entry);
    my_vec_free(&ctx->line_buf, NULL);
    free(ctx->old_pwd);
    ctx->old_pwd = NULL;
    ctx->pipe_fd[0] = -1;
    ctx->pipe_fd[1] = -1;
}
