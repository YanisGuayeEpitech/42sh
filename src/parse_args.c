/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Parses the shell arguments
*/

#include <libmy/printf.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "shell.h"

static bool sh_open_input_script(sh_ctx_t *ctx, char const *path)
{
    my_iostream_t *input = malloc(sizeof(*input));
    struct stat sb;

    if (input == NULL) {
        ctx->exit_code = 1;
        return (bool)sh_rerror(path, SH_OUT_OF_MEMORY, false);
    }
    if (my_fopen(path, "r", input)) {
        sh_perror_errno(path);
        free(input);
        ctx->exit_code = 1;
        return false;
    }
    my_fset_buffer(
        MY_STDIN->unix_stream.buf, MY_STDIN->unix_stream.buf_cap, NULL, input);
    ctx->is_tty = 0;
    ctx->input = input;
    return fstat(input->unix_stream.fd, &sb) != -1 && S_ISREG(sb.st_mode);
}

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
    if (i < ac && !sh_open_input_script(ctx, av[i]))
        return false;
    return true;
}
