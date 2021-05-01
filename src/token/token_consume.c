/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Consumes a token from the given array
*/

#include "token.h"

bool sh_token_consume(
    size_t *token_count, sh_token_t **tokens, sh_token_type_t token_type)
{
    if (*token_count > 0 && (*tokens)->token_type == token_type) {
        ++(*tokens);
        --(*token_count);
        return true;
    }
    return false;
}

bool sh_token_consume_except(
    size_t *token_count, sh_token_t **tokens, sh_token_type_t token_type)
{
    if (*token_count > 0 && (*tokens)->token_type != token_type) {
        ++(*tokens);
        --(*token_count);
        return true;
    }
    return false;
}
