/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Parses the next token
*/

#include "token.h"

static int sh_token_simple(sh_token_type_t token_type, sh_token_t *token)
{
    *token = (sh_token_t){.token_type = token_type};
    return 0;
}

static int sh_token_double(sh_token_stream_t *stream, char lexeme,
    sh_token_type_t token_type, sh_token_t *token)
{
    if (*SH_STREAM_CURRENT(stream, 0) == lexeme) {
        *token = (sh_token_t){.token_type = token_type + 1};
        ++stream->line_pos;
    } else {
        *token = (sh_token_t){.token_type = token_type};
    }
    return 0;
}

int sh_token_parse(sh_token_stream_t *stream, sh_token_t *token)
{
    assert(stream != NULL);
    assert(token != NULL);
    while (stream->line_pos < stream->line_buf.length
        && sh_is_arg_sep(*SH_STREAM_CURRENT(stream, 0)))
        ++stream->line_pos;
    if (sh_token_stream_is_eol(stream))
        return -1;
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
}
