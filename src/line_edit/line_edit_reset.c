/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** line_edit_init
*/

#include <libmy/io.h>

#include "line_edit.h"

int sh_line_edit_reset(sh_line_edit_t *line_edit, my_vec_t *line_buf)
{
    line_edit->line_buf = line_buf;
    line_edit->pos = 0;
    line_edit->is_eof = my_feof(MY_STDIN);
    return 0;
}