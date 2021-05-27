/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** line_edition
*/

#ifndef LINE_EDITION_H_
#define LINE_EDITION_H_

#include <libmy/collections/vec.h>
#include <libmy/io.h>
#include <stdbool.h>
#include <sys/types.h>

#include "keybinds.h"
#include "completion.h"

struct sh_ctx;

typedef struct sh_line_edit {
    my_vec_t *line_buf;
    char *prompt;
    size_t pos;
    bool is_eof;
    struct sh_ctx *ctx;
} sh_line_edit_t;

int sh_line_edit_reset(
    struct sh_ctx *ctx, sh_line_edit_t *line_edit, my_vec_t *line_buf);
ssize_t sh_line_edit_fill(sh_line_edit_t *line_edit, my_iostream_t *stream);
void sh_line_edit_update(sh_line_edit_t *line_edit, my_vec_t *line_buf);

#endif /* !LINE_EDITION_H_ */
