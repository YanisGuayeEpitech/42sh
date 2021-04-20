/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes a token array
*/

#include "shell.h"

static bool sh_lint_pipes(size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;

    while (token_count > 0) {
        end = 0;
        while (end < token_count && tokens[end].token_type != SH_TOKEN_PIPE)
            ++end;
        tokens += end;
        token_count -= end;
        if (sh_token_consume(&token_count, &tokens, SH_TOKEN_PIPE)
            && token_count == 0)
            return (bool)sh_rerror(NULL, SH_INVALID_NULL_COMMAND, false);
    }
    return true;
}

bool sh_lint_tokens(size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;

    while (token_count != 0) {
        end = 0;
        while (sh_token_consume(&token_count, &tokens, SH_TOKEN_SEMICOLON))
            ;
        while (
            end < token_count && tokens[end].token_type != SH_TOKEN_SEMICOLON)
            ++end;
        if (!sh_lint_pipes(end, tokens))
            return false;
        tokens += end;
        token_count -= end;
    }
    return true;
}
