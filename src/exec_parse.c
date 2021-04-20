/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes a token array
*/

#include "shell.h"

static int sh_exec_parse_pipes(
    sh_ctx_t *ctx, size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;
    int ret;

    while (token_count > 0) {
        end = 0;
        while (end < token_count && tokens[end].token_type != SH_TOKEN_PIPE)
            ++end;
        ret = sh_exec_tokens(ctx, end, tokens);
        if (ret != 0)
            return ret;
        tokens += end;
        token_count -= end;
        sh_token_consume(&token_count, &tokens, SH_TOKEN_PIPE);
    }
    return 0;
}

static int sh_exec_parse_semicolons(
    sh_ctx_t *ctx, size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;
    int ret;

    do {
        end = 0;
        while (token_count > 0 && tokens->token_type == SH_TOKEN_SEMICOLON) {
            --token_count;
            ++tokens;
        }
        while (
            end < token_count && tokens[end].token_type != SH_TOKEN_SEMICOLON)
            ++end;
        ret = sh_exec_parse_pipes(ctx, end, tokens) < 0;
        if (ret != 0)
            return 0;
        tokens += end;
        token_count -= end;
    } while (end != 0);
    return 0;
}

int sh_exec_parse(
    sh_ctx_t *ctx, size_t token_count, sh_token_t tokens[token_count])
{
    int ret;

    if (!sh_lint_tokens(token_count, tokens)) {
        ctx->exit_code = 1;
        return 1;
    }
    ret = sh_exec_parse_semicolons(ctx, token_count, tokens);
    if (ret > 0)
        ctx->exit_code = 1;
    return ret;
}
