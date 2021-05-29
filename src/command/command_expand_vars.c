/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Expands all the variables in a command
*/

#include <libmy/ascii.h>
#include <stdlib.h>

#include "command.h"
#include "variables.h"

static ssize_t sh_split_arg_at(
    my_vec_t *args, size_t arg_pos, size_t split_pos)
{
    char *arg = MY_VEC_GET(char *, args, arg_pos);
    size_t first_end = split_pos;
    size_t second_start = split_pos;
    char *second;

    if ((split_pos == 0 || !my_isspace(arg[split_pos - 1]))
        && !my_isspace(arg[arg_pos]))
        return 1;
    while (my_isspace(arg[first_end]))
        ++first_end;
    while (my_isspace(arg[second_start]))
        ++second_start;
    if (arg[second_start] == '\0') {
        if (first_end == 0) {
            free(arg);
            my_vec_remove(args, NULL, arg_pos);
            return 0;
        }
        return 1;
    }
    if (first_end == 0) {
        *((char **)my_vec_get(args, arg_pos)) = arg + second_start;
        return 1;
    }
    second = my_strdup(arg + second_start);
    if (second == NULL || my_vec_insert(args, &second, split_pos + 1)) {
        free(second);
        return (ssize_t)sh_rerror(NULL, SH_OUT_OF_MEMORY, -1);
    }
    arg[first_end + 1] = '\0';
    return 2;
}

static ssize_t sh_split_arg_expansion(
    sh_expansion_t const *exp, my_vec_t *args, size_t arg_pos)
{
    ssize_t arg_count = sh_split_arg_at(args, arg_pos, exp->value_begin);
    sh_lstr_t word;
    char *arg;

    if (arg_count <= 0)
        return arg_count;
    arg = MY_VEC_GET(char *, args, arg_pos + arg_count - 1);
    word = sh_next_word((char const **)&arg);
    while (word.value != NULL) {
        ssize_t ret =
            sh_split_arg_at(args, arg_pos + arg_count - 1, word.value - arg);

        if (ret < 0)
            return -1;
        arg_count += ret;
        arg = MY_VEC_GET(char *, args, arg_count - 1);
        word = sh_next_word((char const **)&arg);
    }
    return arg_count;
}

/// @returns the number of arguments modified/created, or -1 on error.
static ssize_t sh_command_expand_unquoted_str(
    sh_ctx_t *ctx, my_vec_t *args, size_t pos)
{
    sh_expansion_t exp = {.str = MY_VEC_GET(char *, args, pos)};
    sh_lstr_t name;
    size_t arg_count = sh_count_words(exp.str) > 0;

    if (arg_count == 0)
        return 1;

    sh_error_t ret = sh_expand_var(ctx, &exp, &name);

    while (ret == SH_OK && exp.str[exp.value_end] != '\0') {
        ssize_t count =
            sh_split_arg_expansion(&exp, args, pos + arg_count - 1);

        if (count < 0)
            return -1;
        arg_count += count;
        ret = sh_expand_var(ctx, &exp, &name);
    }
    if (!sh_print_var_error(ret, name))
        return -1;
    if (arg_count == 0)
        my_vec_remove(args, NULL, pos);
    return arg_count;
}

static bool sh_command_expand_double_str(
    sh_ctx_t *ctx, my_vec_t *args, size_t pos)
{
    sh_lstr_t name;
    sh_error_t ret = sh_expand_vars(ctx, my_vec_get(args, pos), &name);

    return sh_print_var_error(ret, name);
}

bool sh_command_expand_vars(sh_ctx_t *ctx, sh_command_t *cmd)
{
    size_t arg_count = cmd->base.args.length;
    size_t i = 0;
    int exit_code = ctx->exit_code;

    ctx->exit_code = 1;
    while (i < arg_count - 1) {
        ssize_t next_arg = 1;
        sh_token_type_t type =
            MY_VEC_GET(sh_token_type_t, &cmd->base.arg_types, i);

        if (type == SH_TOKEN_DOUBLE_STR
            && !sh_command_expand_double_str(ctx, &cmd->base.args, i))
            return false;
        if (type == SH_TOKEN_UNQUOTED_STR)
            next_arg = sh_command_expand_unquoted_str(ctx, &cmd->base.args, i);
        if (next_arg < 0)
            return false;
        i += (size_t)next_arg;
    }
    ctx->exit_code = exit_code;
    return true;
}
