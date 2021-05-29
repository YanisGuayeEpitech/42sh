/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Expands a redirect name
*/

#include <libmy/ascii.h>
#include <libmy/printf.h>
#include <stdlib.h>

#include "command.h"
#include "variables.h"

bool sh_command_expand_redirect(
    sh_ctx_t *ctx, char **name, sh_token_type_t *type)
{
    sh_error_t ret;
    sh_lstr_t var_name;

    if (!(*type & (SH_TOKEN_DOUBLE_STR | SH_TOKEN_UNQUOTED_STR))) {
        *type = SH_TOKEN_SINGLE_STR;
        return true;
    }
    ret = sh_expand_vars(ctx, name, &var_name);
    if (!sh_print_var_error(ret, var_name))
        return false;
    if (*type == SH_TOKEN_DOUBLE_STR)
        return true;
    if (sh_count_words(*name) != 1) {
        my_fprintf(
            MY_STDERR, "%.*s: Ambiguous.\n", var_name.length, var_name.value);
        return false;
    }
    return true;
}
