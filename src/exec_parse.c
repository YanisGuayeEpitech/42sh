/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes a token array
*/

#include "shell.h"

int sh_exec_parse(
    sh_ctx_t *ctx, size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;

    do {
        end = 0;
        while (token_count > 0 && tokens->token_type == SH_TOKEN_SEMICOLON) {
            --token_count;
            ++tokens;
        }
        while (
            end < token_count && tokens[end].token_type != SH_TOKEN_SEMICOLON)
            ++end;
        if (sh_exec_tokens(ctx, end, tokens) < 0)
            return -1;
        tokens += end;
        token_count -= end;
    } while (end != 0);
    return 0;
}
