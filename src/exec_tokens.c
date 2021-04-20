/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes a token array
*/

#include "shell.h"

static const char *TOKEN_STR[SH_TOKEN_TYPE_COUNT] = {
    [SH_TOKEN_STRING] = NULL,
    [SH_TOKEN_PIPE] = "|",
    [SH_TOKEN_SEMICOLON] = ";",
    [SH_TOKEN_LT] = "<",
    [SH_TOKEN_GT] = ">",
    [SH_TOKEN_LT_LT] = "<<",
    [SH_TOKEN_GT_GT] = ">>",
};

static const char *sh_token_as_str(sh_token_t const *token)
{
    char const *value = TOKEN_STR[token->token_type];

    return value == NULL ? token->str : value;
}

int sh_exec_tokens(sh_ctx_t *ctx, size_t token_count,
    sh_token_t tokens[token_count], sh_pipe_pos_t pipe_pos)
{
    char const *value;

    my_vec_clear(&ctx->args, NULL);
    if (token_count == 0)
        return 0;
    if (my_vec_ensure_capacity(&ctx->args, token_count + 1) != MY_VEC_OK)
        return sh_rerror(NULL, SH_OUT_OF_MEMORY, 0);
    for (size_t i = 0; i < token_count; ++i) {
        value = sh_token_as_str(&tokens[i]);
        my_vec_push(&ctx->args, &value);
    }
    value = NULL;
    my_vec_push(&ctx->args, &value);
    return sh_exec(ctx, ctx->args.length, ctx->args.data, pipe_pos);
}
