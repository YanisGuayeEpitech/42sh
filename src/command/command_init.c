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
    *command = (sh_command_t){.command_type = SH_COMMAND_INVALID};
    my_vec_init(&command->base.args, sizeof(char *));
}
