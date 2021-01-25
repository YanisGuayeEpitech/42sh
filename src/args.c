/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Parses args from stdin
*/

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

static int sh_read_next_arg(sh_ctx_t *ctx, my_vec_t *args, size_t *pos)
{
    my_vec_t arg;
    char terminator = '\0';

    while (*pos < ctx->line_buf.length
        && sh_is_arg_sep(sh_get_line_buf(ctx)[*pos]))
        ++(*pos);
    if (*pos >= ctx->line_buf.length)
        return 0;
    my_vec_init(&arg, sizeof(char));
    while (*pos < ctx->line_buf.length
        && !sh_is_arg_sep(sh_get_line_buf(ctx)[*pos])) {
        if (sh_copy_char(&arg, sh_get_line_buf(ctx)[*pos]))
            return -1;
        ++(*pos);
    }
    if (my_vec_push(&arg, &terminator) != MY_VEC_OK) {
        my_vec_free(&arg, NULL);
        return -1;
    }
    return my_vec_push(args, &arg.data) == MY_VEC_OK ? 1 : -1;
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
    if (ret < 0 || my_vec_push(args, &elem) != MY_VEC_OK)
        return 0;
    return 1;
}
