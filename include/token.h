/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** User input tokenization
*/

#ifndef __SHELL_INPUT__
#define __SHELL_INPUT__

#include <assert.h>
#include <libmy/collections/vec.h>
#include <stdbool.h>
#include <sys/types.h>

#include "error.h"

typedef enum sh_token_type {
    SH_TOKEN_STRING,
    SH_TOKEN_PIPE,
    SH_TOKEN_SEMICOLON,
    SH_TOKEN_LT,
    SH_TOKEN_LT_LT,
    SH_TOKEN_GT,
    SH_TOKEN_GT_GT,
    SH_TOKEN_TYPE_COUNT,
} sh_token_type_t;

typedef struct sh_token {
    sh_token_type_t token_type;
    union {
        /// Allocated string representation of this token, only present when
        /// @c token_type is @c SH_TOKEN_STRING.
        char *str;
    };
} sh_token_t;

typedef struct sh_token_stream {
    /// The current line buffer.
    /// Element type: char
    my_vec_t line_buf;
    /// Current tokens buffer.
    /// Element type: sh_token_t;
    my_vec_t tokens;
    size_t line_pos;
} sh_token_stream_t;

void sh_token_stream_init(sh_token_stream_t *stream);
void sh_token_stream_reset(sh_token_stream_t *stream);
void sh_token_stream_drop(sh_token_stream_t *stream);

/// @returns 0 on success, 1 on token error, or -1 on EOL.
int sh_token_parse(sh_token_stream_t *stream, sh_token_t *token);

ssize_t sh_token_stream_push(sh_token_stream_t *stream, size_t token_count);

SH_INLINE ssize_t sh_token_stream_next(
    sh_token_stream_t *stream, size_t token_count)
{
    sh_token_stream_reset(stream);
    return sh_token_stream_push(stream, token_count);
}

SH_INLINE bool sh_token_stream_is_eol(sh_token_stream_t const *stream)
{
    assert(stream != NULL);
    return stream->line_pos >= stream->line_buf.length;
}

void sh_drop_token(void *token);

char *sh_token_to_str(sh_token_t *token);

/// Is @c c an argument separator character?
///
/// @param c The character to check
///
/// @returns Whether the given character is an argument separator.
SH_INLINE bool sh_is_arg_sep(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

SH_INLINE bool sh_is_token_char(char c)
{
    return c == '"' || c == '\'' || c == '|' || c == ';' || c == '<'
        || c == '>';
}

bool sh_token_consume(
    size_t *token_count, sh_token_t **tokens, sh_token_type_t token_type);

bool sh_token_consume_except(
    size_t *token_count, sh_token_t **tokens, sh_token_type_t token_type);

/// @returns 0 on success, 1 on token error, or -1 on EOL.
int sh_token_quoted_string(
    sh_token_stream_t *stream, sh_token_t *token, char term);
/// @returns 0 on success, 1 on token error, or -1 on EOL.
int sh_token_unquoted_string(sh_token_stream_t *stream, sh_token_t *token);

#define SH_STREAM_LINE(stream)           ((char *)(stream)->line_buf.data)
#define SH_STREAM_OFFSET(stream, offset) (SH_STREAM_LINE((stream)) + (offset))
#define SH_STREAM_CURRENT(stream, offset) \
    (SH_STREAM_OFFSET((stream), (stream)->line_pos) + (offset))
#define SH_STREAM_CURRENT_LEN(stream) \
    ((stream)->line_buf.length - (stream)->line_pos)

#endif // !defined(__SHELL_INPUT__)
