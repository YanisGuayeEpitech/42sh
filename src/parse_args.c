/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Parses the shell arguments
*/

#include <libmy/printf.h>

#include "shell.h"

bool sh_parse_args(sh_ctx_t *ctx, int ac, char *av[])
{
    int i = 1;

    while (i < ac) {
        if (av[i][0] != '-' || av[i][1] == 'b') {
            i += av[i][1] == 'b';
            break;
        }
        my_fprintf(MY_STDERR,
            "Unknown option: `%s'\nUsage: %s [ -b ] [ argument ... ].\n",
            av[i], av[0]);
        ctx->exit_code = 1;
        return false;
    }
    if (i < ac && !sh_open_script(ctx, av[i]))
        return false;
    return true;
}
