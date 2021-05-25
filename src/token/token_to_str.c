/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Converts a token to an allocated string
*/

#include <assert.h>
#include <libmy/ascii/ascii.h>

#include "token.h"

static const char *SH_TOKEN_STR[SH_TOKEN_TYPE_COUNT] = {
    [SH_TOKEN_STRING] = NULL,
    [SH_TOKEN_PIPE] = "|",
    [SH_TOKEN_PIPE_PIPE] = "||",
    [SH_TOKEN_SEMICOLON] = ";",
    [SH_TOKEN_LT] = "<",
    [SH_TOKEN_GT] = ">",
    [SH_TOKEN_LT_LT] = "<<",
    [SH_TOKEN_GT_GT] = ">>",
    [SH_TOKEN_AND] = "&",
    [SH_TOKEN_AND_AND] = "&&",
};

char *sh_token_to_str(sh_token_t *token)
{
    assert(token->token_type >= 0 && token->token_type < SH_TOKEN_TYPE_COUNT);
    if (token->token_type == SH_TOKEN_STRING) {
        char *value = token->str;

        token->str = NULL;
        return value;
    }
    return my_strdup(SH_TOKEN_STR[token->token_type]);
}
