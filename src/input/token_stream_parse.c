/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Parses the next token
*/

#include <libmy/memory/alloc.h>
#include <libmy/printf.h>
#include <stdlib.h>

#include "input.h"

static bool sh_token_stream_fill_line(sh_token_stream_t *stream)
{
    ssize_t bytes_read = my_getline(
        (char **)&stream->line_buf.data, &stream->line_buf.capacity, MY_STDIN);

    stream->line_buf.length = bytes_read < 0 ? 0 : (size_t)bytes_read;
    stream->line_pos = 0;
    return bytes_read > 0;
}

static bool sh_token_simple(sh_token_type_t token_type, sh_token_t *token)
{
    *token = (sh_token_t){.token_type = token_type};
    return true;
}

static bool sh_token_double(sh_token_stream_t *stream, char lexeme,
    sh_token_type_t token_type, sh_token_t *token)
{
    if (*SH_STREAM_CURRENT(stream, 0) == lexeme) {
        *token = (sh_token_t){.token_type = token_type + 1};
        ++stream->line_pos;
    } else {
        *token = (sh_token_t){.token_type = token_type};
    }
    return true;
}

bool sh_token_stream_parse(sh_token_stream_t *stream, sh_token_t *token)
{
    assert(stream != NULL);
    assert(token != NULL);
    if (sh_token_stream_is_eol(stream) && !sh_token_stream_fill_line(stream))
        return true;
    while (stream->line_pos < stream->line_buf.length
        && sh_is_arg_sep(*SH_STREAM_CURRENT(stream, 0)))
        ++stream->line_pos;
    if (sh_token_stream_is_eol(stream))
        return true;
    ++stream->line_pos;
    switch (*SH_STREAM_CURRENT(stream, -1)) {
        case '|': return sh_token_simple(SH_TOKEN_PIPE, token);
        case ';': return sh_token_simple(SH_TOKEN_SEMICOLON, token);
        case '"': return sh_token_quoted_string(stream, token, '"');
        case '\'': return sh_token_quoted_string(stream, token, '\'');
        case '<': return sh_token_double(stream, '<', SH_TOKEN_LT, token);
        case '>': return sh_token_double(stream, '>', SH_TOKEN_GT, token);
        default: return sh_token_unquoted_string(stream, token);
    }
    return true;
}
