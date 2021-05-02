/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Intitalizes a command struct
*/

#include <assert.h>

#include "command.h"

void sh_command_init(sh_command_t *command)
{
    *command = (sh_command_t){
        .base =
            {
                .command_type = SH_COMMAND_UNRESOLVED,
                .input_fd = -1,
                .output_fd = -1,
            },
    };
    my_vec_init(&command->base.args, sizeof(char *));
}
