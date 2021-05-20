/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Parses string tokens
*/

#include <assert.h>
#include <libmy/memory/alloc.h>
#include <libmy/printf.h>
#include <stdlib.h>

#include "token.h"

static size_t sh_token_quoted_string_get_len(char *src, size_t src_len)
{
    size_t len = src_len;
    bool inhibitor = false;

    assert(src != NULL);
    for (size_t i = 0; i < len; i++) {
        inhibitor = (src[i] == SH_INHIBITOR) && !inhibitor;
        len -= (inhibitor && len);
    }
    return len;
}

static char *sh_token_quoted_string_copy(char *src, size_t src_len)
{
    size_t len = sh_token_quoted_string_get_len(src, src_len);
    char *str = NULL;
    bool inhibitor = false;

    if (len == 0)
        return NULL;
    str = malloc(sizeof(char) * len);
    if (!str)
        return NULL;
    len = 0;
    for (size_t i = 0; i < src_len; i++) {
        inhibitor = (src[i] == SH_INHIBITOR) && !inhibitor;
        if (inhibitor)
            continue;
        str[len++] = src[i];
    }
    str[len - 1] = 0;
    return str;
}

char *sh_token_quoted_string_get_end(char *str, char term, size_t len)
{
    bool inhibitor = false;
    bool all_quotes = (term == 0);

    if (str == NULL)
        return NULL;
    for (size_t i = 0; i < len; i++) {
        if (!inhibitor && ((!all_quotes && str[i] == term) || \
            (all_quotes && (str[i] == '\'' || str[i] == '\"'))))
            return str + i;
        inhibitor = (str[i] == SH_INHIBITOR) && !inhibitor;
    }
    return NULL;
}

int sh_token_quoted_string(
    sh_token_stream_t *stream, sh_token_t *token, char term)
{
    char *end = sh_token_quoted_string_get_end(
        SH_STREAM_CURRENT(stream, 0), term, SH_STREAM_CURRENT_LEN(stream));
    size_t len;

    if (end == NULL)
        return 0;
    len = (end - SH_STREAM_CURRENT(stream, 0)) + 1;
    *token = (sh_token_t){.token_type = SH_TOKEN_STRING,
        .str = sh_token_quoted_string_copy(SH_STREAM_CURRENT(stream, 0), len)};
    if (token->str == NULL)
        return 1;
    stream->line_pos += len;
    return 0;
}
