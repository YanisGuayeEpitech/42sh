/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Opens a script
*/

#include <stdlib.h>
#include <sys/stat.h>

#include "shell.h"

bool sh_open_script(sh_ctx_t *ctx, char const *path)
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
