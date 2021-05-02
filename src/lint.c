/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Executes a token array
*/

#include "shell.h"

static bool sh_lint_input_redirects(
    size_t token_count, sh_token_t tokens[token_count], sh_error_t *err)
{
    bool has_redirect = false;

    while (token_count > 0) {
        bool new_redirect = sh_token_consume_until(
            &token_count, &tokens, SH_TOKEN_LT | SH_TOKEN_LT_LT);

        if (sh_token_consume(
                &token_count, &tokens, SH_TOKEN_LT | SH_TOKEN_LT_LT)
            && !sh_token_consume(&token_count, &tokens, SH_TOKEN_STRING))
            return sh_serror(err, SH_MISSING_REDIRECT_NAME, false);
        if (has_redirect && new_redirect)
            return sh_serror(err, SH_AMBIGUOUS_INPUT_REDIRECT, false);
        has_redirect |= new_redirect;
    }
    return true;
}

static int sh_lint_output_redirects(
    size_t token_count, sh_token_t tokens[token_count], sh_error_t *err)
{
    bool has_redirect = false;

    while (token_count > 0) {
        bool new_redirect = sh_token_consume_until(
            &token_count, &tokens, SH_TOKEN_GT | SH_TOKEN_GT_GT);

        if (sh_token_consume(
                &token_count, &tokens, SH_TOKEN_GT | SH_TOKEN_GT_GT)
            && !sh_token_consume(&token_count, &tokens, SH_TOKEN_STRING))
            return sh_serror(err, SH_MISSING_REDIRECT_NAME, -1);
        if (has_redirect && new_redirect)
            return 2;
        has_redirect |= new_redirect;
    }
    return (int)has_redirect;
}

static bool sh_lint_pipes(
    size_t token_count, sh_token_t tokens[token_count], sh_error_t *err)
{
    size_t end;
    int redirect_count = sh_lint_output_redirects(token_count, tokens, err);

    if (redirect_count < 0
        || !sh_lint_input_redirects(token_count, tokens, err))
        return false;
    while (token_count > 0) {
        end = sh_token_find(token_count, tokens, SH_TOKEN_PIPE);
        if (redirect_count + (end < token_count) > 1)
            return sh_serror(err, SH_AMBIGUOUS_OUTPUT_REDIRECT, false);
        sh_token_advance(&token_count, &tokens, end);
        if (sh_token_consume(&token_count, &tokens, SH_TOKEN_PIPE)
            && token_count == 0)
            return sh_serror(err, SH_INVALID_NULL_COMMAND, false);
    }
    return true;
}

sh_error_t sh_lint(size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;

    while (token_count != 0) {
        sh_error_t err;

        sh_token_consume_while(&token_count, &tokens, SH_TOKEN_SEMICOLON);
        end = sh_token_find(token_count, tokens, SH_TOKEN_SEMICOLON);
        if (!sh_lint_pipes(end, tokens, &err))
            return err;
        sh_token_advance(&token_count, &tokens, end);
    }
    return SH_OK;
}
