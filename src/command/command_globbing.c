/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Parses the next command
*/

#include <glob.h>
#include <libmy/ascii.h>
#include <libmy/collections.h>
#include <stdlib.h>
#include <sys/types.h>

#include "builtin.h"
#include "command.h"
#include "util.h"

static int fill_globbuf(
    glob_t *globbuf, sh_command_t *command, size_t *nb_args)
{
    char *arg;
    int flags = GLOB_TILDE;
    int return_code = 0;

    globfree(globbuf);
    globbuf->gl_pathc = 0;
    for (size_t i = 1; i < *nb_args - 1; i++) {
        arg = MY_VEC_GET(char *, &command->base.args, i);
        return_code = glob(arg, flags, NULL, globbuf);
        if (return_code == GLOB_NOSPACE || return_code == GLOB_ABORTED)
            break;
        if (i == 1)
            flags |= GLOB_APPEND;
        if (return_code == 0) {
            my_vec_remove(&command->base.args, NULL, i);
            free(arg);
            i--;
            (*nb_args)--;
        }
    }
    return return_code;
}

static void handle_globbuf(
    sh_ctx_t *ctx, sh_command_t *command, glob_t *globbuf, size_t nb_args)
{
    char *arg;

    my_vec_remove(&command->base.args, &arg, nb_args - 1);
    free(arg);
    for (size_t i = 0; i < globbuf->gl_pathc; i++) {
        arg = my_strdup(globbuf->gl_pathv[i]);
        my_vec_push(&command->base.args, &arg);
    }
    globfree(globbuf);
    if (!globbuf->gl_pathc) {
        ctx->exit_code = 1;
        sh_perror(MY_VEC_GET(char *, &command->base.args, 0), SH_NO_MATCH);
    }
}

static bool has_globbing_chars(
    glob_t *globbuf, sh_command_t *command, size_t nb_args)
{
    char *arg;
    int flags = GLOB_TILDE | GLOB_NOMAGIC;
    int return_code = 0;

    globbuf->gl_offs = 0;
    globbuf->gl_pathc = 0;
    for (size_t i = 1; i < nb_args - 1; i++) {
        arg = MY_VEC_GET(char *, &command->base.args, i);
        return_code = glob(arg, flags, NULL, globbuf);
        if (return_code == GLOB_NOSPACE || return_code == GLOB_ABORTED)
            break;
        if (i == 1)
            flags |= GLOB_APPEND;
    }
    if (nb_args - 2 != globbuf->gl_pathc)
        return true;
    for (size_t i = 1; i < nb_args - 1; i++)
        if (my_strcmp(MY_VEC_GET(char *, &command->base.args, i),
                globbuf->gl_pathv[i - 1]))
            return true;
    return false;
}

bool sh_command_globbing(sh_ctx_t *ctx, sh_command_t *command)
{
    glob_t globbuf;
    char *arg;
    int return_code = 0;
    size_t nb_args = command->base.args.length;

    if (nb_args <= 2)
        return true;
    if (!has_globbing_chars(&globbuf, command, nb_args)) {
        globfree(&globbuf);
        return true;
    }
    return_code = fill_globbuf(&globbuf, command, &nb_args);
    handle_globbuf(ctx, command, &globbuf, nb_args);
    arg = NULL;
    my_vec_push(&command->base.args, &arg);
    return (return_code != GLOB_NOSPACE && return_code != GLOB_ABORTED
        && globbuf.gl_pathc);
}
