/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Uninitializes a token stream
*/

#include <stdlib.h>

#include "input.h"

static void sh_free_token(void *token)
{
    sh_token_t *t = token;

    switch (t->token_type) {
        case SH_TOKEN_STRING: free(t->str); break;
        default: break;
    }
    *t = (sh_token_t){0};
}

void sh_token_stream_drop(sh_token_stream_t *stream)
{
    if (stream == NULL)
        return;
    my_vec_free(&stream->line_buf, NULL);
    my_vec_free(&stream->line_buf, &sh_free_token);
}
