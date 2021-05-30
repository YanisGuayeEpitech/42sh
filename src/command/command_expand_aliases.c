/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Expands the aliases in the first argument, recursively
*/

#include <libmy/ascii/ascii.h>
#include <stdlib.h>

#include "command.h"

static bool sh_command_get_alias(
    sh_ctx_t *ctx, my_vec_t *args, sh_alias_t *alias, char *excluded)
{
    sh_lstr_t arg = SH_TO_LSTR(MY_VEC_GET(char *, args, 0));
    sh_alias_t *value;

    if (excluded != NULL && my_strcmp(arg.value, excluded) == 0)
        return false;
    value = my_hash_map_get(&ctx->aliases, &arg);
    if (value == NULL)
        return false;
    *alias = *value;
    return true;
}

static void sh_command_alias_init_stream(
    sh_token_stream_t *stream, sh_alias_t const *alias)
{
    sh_token_stream_init(stream);
    stream->line_buf.data = my_strndup(alias->value, alias->length);
    stream->line_buf.capacity = alias->length;
    stream->line_buf.length = alias->length;
}

static bool sh_command_alias_insert_alias(
    sh_ctx_t *ctx, sh_command_base_t *command, sh_alias_t const *alias)
{
    sh_token_stream_t stream;
    sh_token_t token;
    size_t pos = 0;

    sh_command_alias_init_stream(&stream, alias);
    while (sh_token_parse(&stream, ctx, &token) == 0) {
        if (!sh_token_into_str(&token)
            || my_vec_insert(&command->args, &token.str, pos)) {
            sh_token_stream_drop(&stream);
            sh_drop_token(&token);
            return false;
        }
        if (my_vec_insert(&command->arg_types, &token.type, pos)) {
            sh_token_stream_drop(&stream);
            return false;
        }
        ++pos;
    }
    sh_token_stream_drop(&stream);
    return true;
}

bool sh_command_expand_aliases(sh_ctx_t *ctx, sh_command_t *command)
{
    sh_alias_t alias;
    char *previous = NULL;

    if (!sh_command_get_alias(ctx, &command->base.args, &alias, NULL))
        return true;
    do {
        free(previous);
        my_vec_remove(&command->base.args, &previous, 0);
        my_vec_remove(&command->base.arg_types, NULL, 0);
        if (!sh_command_alias_insert_alias(ctx, &command->base, &alias))
            return (bool)sh_rerror(NULL, SH_OUT_OF_MEMORY, false);
    } while (sh_command_get_alias(ctx, &command->base.args, &alias, previous));
    free(previous);
    sh_command_resolve(ctx, command);
    return true;
}
