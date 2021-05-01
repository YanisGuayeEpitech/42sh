/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Parses the next command
*/

#include <assert.h>

#include "command.h"

int sh_command_parse(sh_command_t *command, size_t token_count,
    sh_token_t tokens[token_count], sh_pipe_pos_t pipe_pos)
{
    char const *value;

    assert(tokens != NULL);
    assert(pipe_pos >= 0 && pipe_pos < SH_PIPE_INVALID);
    if (command == NULL)
        return sh_rerror(NULL, SH_OUT_OF_MEMORY, 0);
    command->base.pipe_pos = pipe_pos;
    if (my_vec_ensure_capacity(&command->base.args, token_count + 1))
        return sh_rerror(NULL, SH_OUT_OF_MEMORY, 1);
    for (size_t i = 0; i < token_count; ++i) {
        value = sh_token_to_str(&tokens[i]);
        my_vec_push(&command->base.args, &value);
    }
    value = NULL;
    my_vec_push(&command->base.args, &value);
    return 0;
}
