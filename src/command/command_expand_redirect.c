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
    char *old_name = *type == SH_TOKEN_UNQUOTED_STR ? my_strdup(*name) : NULL;

    if (!(*type & (SH_TOKEN_DOUBLE_STR | SH_TOKEN_UNQUOTED_STR))) {
        *type = SH_TOKEN_SINGLE_STR;
        return true;
    }
    ret = sh_expand_vars(ctx, name);
    if (*type == SH_TOKEN_DOUBLE_STR || ret != SH_OK)
        return (bool)sh_rerror(NULL, ret, *type == SH_TOKEN_DOUBLE_STR);
    if (sh_count_words(*name) != 1) {
        my_fprintf(MY_STDERR, "%s: Ambiguous.\n", old_name);
        free(old_name);
        return false;
    }
    free(old_name);
    return true;
}
