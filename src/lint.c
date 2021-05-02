/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes a token array
*/

#include "shell.h"

static bool sh_lint_input_redirects(
    size_t token_count, sh_token_t tokens[token_count])
{
    bool has_redirect = false;

    while (token_count > 0) {
        bool new_redirect = sh_token_consume_until(
            &token_count, &tokens, SH_TOKEN_LT | SH_TOKEN_LT_LT);

        if (sh_token_consume(
                &token_count, &tokens, SH_TOKEN_LT | SH_TOKEN_LT_LT)
            && !sh_token_consume(&token_count, &tokens, SH_TOKEN_STRING))
            return (bool)sh_rerror(NULL, SH_MISSING_REDIRECT_NAME, false);
        if (has_redirect && new_redirect)
            return (bool)sh_rerror(NULL, SH_AMBIGUOUS_INPUT_REDIRECT, false);
        has_redirect |= new_redirect;
    }
    return true;
}

static bool sh_lint_pipes(size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;

    while (token_count > 0) {
        end = sh_token_find(token_count, tokens, SH_TOKEN_PIPE);
        if (!sh_lint_input_redirects(end, tokens))
            return false;
        tokens += end;
        token_count -= end;
        if (sh_token_consume(&token_count, &tokens, SH_TOKEN_PIPE)
            && token_count == 0)
            return (bool)sh_rerror(NULL, SH_INVALID_NULL_COMMAND, false);
    }
    return true;
}

bool sh_lint(size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;

    while (token_count != 0) {
        sh_token_consume_while(&token_count, &tokens, SH_TOKEN_SEMICOLON);
        end = sh_token_find(token_count, tokens, SH_TOKEN_SEMICOLON);
        if (!sh_lint_pipes(end, tokens))
            return false;
        tokens += end;
        token_count -= end;
    }
    return true;
}
