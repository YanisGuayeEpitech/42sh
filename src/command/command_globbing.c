/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Parses the next command
*/

#include <glob.h>
#include <libmy/collections.h>
#include <sys/types.h>
#include <stdlib.h>

#include "builtin.h"
#include "command.h"
#include "util.h"

bool sh_command_globbing(sh_ctx_t *ctx, sh_command_t *command)
{
    glob_t globbuf;
    size_t nb_args = command->base.args.length;
    char *arg;
    int flags = GLOB_NOMAGIC | GLOB_TILDE;
    int return_code = 0;

    globbuf.gl_offs = 0;
    globbuf.gl_pathc = 0;
    for (size_t i = 1; i < nb_args; i++) {
        arg = MY_VEC_GET(char *, &command->base.args, i);
        return_code = glob(arg, flags, NULL, &globbuf);
        if (return_code == GLOB_NOSPACE || return_code == GLOB_ABORTED)
            break;
        if (i == 1)
            flags |= GLOB_APPEND;
        if (return_code == 0) {
            my_vec_remove(&command->base.args, NULL, i);
            free(arg);
            i--;
            nb_args--;
        }
    }
    if (globbuf.gl_pathc)
        my_vec_remove(&command->base.args, NULL, nb_args - 1);
    for (size_t i = 0; i < globbuf.gl_pathc; i++) {
        arg = my_strdup(globbuf.gl_pathv[i]);
        my_vec_push(&command->base.args, &arg);
    }
    if (globbuf.gl_pathc) {
        arg = NULL;
        my_vec_push(&command->base.args, &arg);
    }
    globfree(&globbuf);
    return (return_code != GLOB_NOSPACE && return_code != GLOB_ABORTED);
}
