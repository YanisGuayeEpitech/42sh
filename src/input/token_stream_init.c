/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Initializes a token stream
*/

#include "input.h"

void sh_token_stream_init(sh_token_stream_t *stream)
{
    assert(stream != NULL);
    my_vec_init(&stream->line_buf, sizeof(char));
    my_vec_init(&stream->tokens, sizeof(sh_token_t));
    sh_token_stream_reset(stream);
}

void sh_token_stream_reset(sh_token_stream_t *stream)
{
    assert(stream != NULL);
    stream->line_buf.length = 0;
    my_vec_clear(&stream->tokens, &sh_drop_token);
    stream->line_pos = 0;
}
