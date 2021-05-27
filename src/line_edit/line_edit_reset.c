/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** line_edit_init
*/

#include <libmy/io.h>
#include <libmy/printf.h>
#include <stdio.h>
#include <unistd.h>

#include "shell.h"

int sh_line_edit_reset(
    struct sh_ctx_s *ctx, sh_line_edit_t *line_edit, my_vec_t *line_buf)
{
    line_edit->line_buf = line_buf;
    line_edit->pos = 0;
    line_edit->is_eof = my_feof(MY_STDIN);
    line_edit->ctx = ctx;
    return 0;
}

void sh_line_edit_update(sh_line_edit_t *line_edit, my_vec_t *line_buf)
{
    size_t back_steps_write = line_buf->length - line_edit->pos;
    char back_buff_aft_write[back_steps_write];
    char tmp[] = "\x1b[2K\r";

    if (!isatty(STDIN_FILENO))
        return;
    write(STDOUT_FILENO, tmp, 5);
    sh_print_prompt(line_edit->ctx);
    write(STDOUT_FILENO, line_buf->data, line_buf->length);
    for (size_t i = 0; i < back_steps_write; i++)
        back_buff_aft_write[i] = '\b';
    write(STDOUT_FILENO, back_buff_aft_write, back_steps_write);
}
