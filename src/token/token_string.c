/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Parses string tokens
*/

#include <libmy/memory/alloc.h>
#include <libmy/printf.h>
#include <stdlib.h>

#include "token.h"

int sh_token_quoted_string(
    sh_token_stream_t *stream, sh_token_t *token, char term)
{
    char *end = my_memchr(
        SH_STREAM_CURRENT(stream, 0), term, SH_STREAM_CURRENT_LEN(stream));
    size_t len;

    if (end == NULL) {
        my_fprintf(MY_STDERR, "Unmatched '%c'\n", end);
        my_flush_stderr();
        return 1;
    }
    len = (end - SH_STREAM_CURRENT(stream, 0)) + 1;
    *token = (sh_token_t){.token_type = SH_TOKEN_STRING,
        .str = my_memdup(SH_STREAM_CURRENT(stream, 0), sizeof(char) * len)};
    if (token->str == NULL)
        return 1;
    token->str[len - 1] = '\0';
    stream->line_pos += len;
    return 0;
}

static ssize_t sh_token_unquoted_string_copy(
    sh_token_stream_t *stream, my_vec_t *str)
{
    size_t buf_len = stream->line_buf.length;
    size_t len = 0;
    char c;
    int escape = 0;

    --stream->line_pos;
    my_vec_init(str, sizeof(char));
    for (; stream->line_pos + len < buf_len; ++len) {
        c = *SH_STREAM_CURRENT(stream, len);
        if (!escape && (sh_is_arg_sep(c) || sh_is_token_char(c)))
            break;
        if ((c != SH_INHIBITOR || escape)
            && my_vec_push(str, &c) != MY_VEC_OK) {
            my_vec_free(str, NULL);
            return -1;
        }
        escape = (c == SH_INHIBITOR) && !escape;
    }
    return len;
}

int sh_token_unquoted_string(sh_token_stream_t *stream, sh_token_t *token)
{
    my_vec_t str;
    ssize_t len = sh_token_unquoted_string_copy(stream, &str);
    char c = '\0';

    if (len < 0 || my_vec_push(&str, &c) != MY_VEC_OK) {
        my_vec_free(&str, NULL);
        return 1;
    }
    *token = (sh_token_t){.token_type = SH_TOKEN_STRING, .str = str.data};
    stream->line_pos += len;
    return 0;
}
