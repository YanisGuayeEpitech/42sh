/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Starts the shell
*/

#include "input.h"
#include "shell.h"

static const char *TOKEN_STR[SH_TOKEN_TYPE_COUNT] = {
    [SH_TOKEN_STRING] = NULL,
    [SH_TOKEN_PIPE] = "|",
    [SH_TOKEN_SEMICOLON] = ";",
};

static const char *sh_token_as_str(sh_token_t const *token)
{
    char const *value = TOKEN_STR[token->token_type];

    return value == NULL ? token->str : value;
}

static ssize_t sh_token_to_args(sh_token_stream_t *stream, my_vec_t *args)
{
    ssize_t token_count = sh_token_stream_next(stream, SIZE_MAX);
    char const *value;

    args->length = 0;
    if (token_count < 0)
        return token_count;
    for (size_t i = 0; i < stream->tokens.length; ++i) {
        value = sh_token_as_str(my_vec_get(&stream->tokens, i));
        if (my_vec_push(args, &value) != MY_VEC_OK)
            return -1;
    }
    value = NULL;
    if (my_vec_push(args, &value) != MY_VEC_OK)
        return -1;
    return token_count;
}

void sh_start(sh_ctx_t *ctx)
{
    sh_token_stream_t stream;
    my_vec_t args;

    sh_token_stream_init(&stream);
    my_vec_init(&args, sizeof(char *));
    sh_print_prompt(ctx);
    while (sh_token_to_args(&stream, &args) >= 0) {
        if (stream.tokens.length > 1
            && sh_exec(ctx, args.length - 1, (char const **)args.data) < 0)
            break;
        sh_print_prompt(ctx);
    }
    sh_print(ctx, "exit\n");
    my_vec_free(&args, &sh_free_entry);
    sh_token_stream_drop(&stream);
}
