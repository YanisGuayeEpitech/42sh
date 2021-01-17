/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Starts the shell
*/

#include "shell.h"

void sh_start(sh_ctx_t *ctx)
{
    my_vec_t args;

    my_vec_init(&args, sizeof(char *));
    sh_print_prompt(ctx);
    while (sh_read_args(ctx, &args) && args.length > 1) {
        if (sh_exec(ctx, args.length - 1, (char const **)args.data) < 0)
            break;
        sh_print_prompt(ctx);
    }
    sh_print(ctx, "exit\n");
    my_vec_free(&args, &sh_free_entry);
}
