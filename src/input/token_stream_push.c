/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Parses n tokens to the token buffer
*/

#include "input.h"

ssize_t sh_token_stream_push(sh_token_stream_t *stream, size_t token_count)
{
    size_t c = 1;

    assert(stream != NULL);
    if (token_count == 0)
        return 0;
    for (; c < token_count; ++c) {
        if (my_vec_reserve(&stream->tokens, 1) != MY_VEC_OK)
            return SH_OUT_OF_MEMORY;
        if (!sh_token_parse(
                stream, my_vec_get(&stream->tokens, stream->tokens.length)))
            return -1;
        if (sh_token_stream_is_eol(stream))
            break;
        ++stream->tokens.length;
    }
    return c;
}
