/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Parses args from stdin
*/

#include <libmy/printf.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

static int sh_copy_char(my_vec_t *arg, char c)
{
    if (c == '\0' || my_vec_push(arg, &c) == MY_VEC_OK)
        return 0;
    my_vec_free(arg, NULL);
    return -1;
}

static int sh_read_unquoted_arg(sh_ctx_t *ctx, my_vec_t *arg, size_t *pos)
{
    char c;

    while (*pos < ctx->line_buf.length) {
        c = sh_get_line_buf(ctx)[*pos];
        if (c == '"' || c == '\'')
            break;
        if (sh_copy_char(arg, c))
            return -1;
        ++(*pos);
    }
    return 1;
}

static int sh_read_quoted_arg(
    sh_ctx_t *ctx, my_vec_t *arg, size_t *pos, char end)
{
    char c;

    ++(*pos);
    while (*pos < ctx->line_buf.length) {
        c = sh_get_line_buf(ctx)[*pos];
        if (c == end)
            break;
        if (sh_copy_char(arg, c))
            return -1;
        ++(*pos);
    }
    if (*pos >= ctx->line_buf.length) {
        my_fprintf(MY_STDERR, "Unmatched '%c'\n", end);
        my_flush_stderr();
        return -2;
    }
    ++(*pos);
    return 1;
}

static int sh_read_next_arg(sh_ctx_t *ctx, my_vec_t *args, size_t *pos)
{
    my_vec_t arg;
    int ret;

    while (*pos < ctx->line_buf.length)
        ++(*pos);
    if (*pos >= ctx->line_buf.length)
        return 0;
    my_vec_init(&arg, sizeof(char));
    if (sh_get_line_buf(ctx)[*pos] == '\''
        || sh_get_line_buf(ctx)[*pos] == '"')
        ret = sh_read_quoted_arg(ctx, &arg, pos, sh_get_line_buf(ctx)[*pos]);
    else
        ret = sh_read_unquoted_arg(ctx, &arg, pos);
    if (ret == -1 || my_vec_push(&arg, "") != MY_VEC_OK) {
        my_vec_free(&arg, NULL);
        return -1;
    }
    return my_vec_push(args, &arg.data) == MY_VEC_OK ? ret : -1;
}

int sh_read_args(sh_ctx_t *ctx, my_vec_t *args)
{
    char *elem = NULL;
    int ret = -1;
    size_t pos = 0;

    for (size_t i = 0; i < args->length; ++i)
        free(MY_VEC_GET_ELEM(char *, args, i));
    args->length = 0;
    if (sh_read_line(ctx) > 0) {
        ret = 42;
        while (ret > 0)
            ret = sh_read_next_arg(ctx, args, &pos);
    }
    if (ret == -2) {
        ctx->exit_code = 1;
        args->length = 0;
    }
    if (ret == -1 || my_vec_push(args, &elem) != MY_VEC_OK)
        return 0;
    return 1;
}
