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

static bool sh_token_quoted_string(
    sh_token_stream_t *stream, sh_token_t *token, char term)
{
    char *end = my_memchr(
        SH_STREAM_CURRENT(stream, 0), term, SH_STREAM_CURRENT_LEN(stream));
    size_t len;

    if (end == NULL) {
        my_fprintf(MY_STDERR, "Unmatched '%c'\n", end);
        my_flush_stderr();
        return false;
    }
    len = (end - SH_STREAM_CURRENT(stream, 0));
    token->str = my_memdup(SH_STREAM_CURRENT(stream, 0), sizeof(char) * len);
    if (token->str == NULL)
        return false;
    token->str[len] = '\0';
    stream->line_pos += len + 1;
    return true;
}

static bool sh_token_unquoted_string(
    sh_token_stream_t *stream, sh_token_t *token)
{
    my_vec_t str;
    size_t buf_len = stream->line_buf.length - 1;
    size_t len = 0;
    char c;

    --stream->line_pos;
    my_vec_init(&str, sizeof(char));
    for (; stream->line_pos + len < buf_len; ++len) {
        c = *SH_STREAM_CURRENT(stream, len);
        if (sh_is_arg_sep(c) || c == '"' || c == '\'')
            break;
        if (my_vec_push(&str, &c) != MY_VEC_OK) {
            my_vec_free(&str, NULL);
            return false;
        }
    }
    token->str = str.data;
    stream->line_pos += len;
    return true;
}

static bool sh_token_stream_fill_line(sh_token_stream_t *stream)
{
    ssize_t bytes_read = my_getline(
        (char **)&stream->line_buf.data, &stream->line_buf.capacity, MY_STDIN);

    stream->line_buf.length = bytes_read < 0 ? 0 : (size_t)bytes_read;
    stream->line_pos = 0;
    return bytes_read > 0;
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
        case '|': *token = (sh_token_t){.token_type = SH_TOKEN_PIPE}; break;
        case ';':
            *token = (sh_token_t){.token_type = SH_TOKEN_SEMICOLON};
            break;
        case '"': return sh_token_quoted_string(stream, token, '"');
        case '\'': return sh_token_quoted_string(stream, token, '\'');
        default: return sh_token_unquoted_string(stream, token);
    }
    return true;
}
