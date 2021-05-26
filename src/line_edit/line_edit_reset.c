/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** line_edit_init
*/

#include <libmy/io.h>
#include <unistd.h>

#include "line_edit.h"

int sh_line_edit_reset(sh_line_edit_t *line_edit, my_vec_t *line_buf)
{
    line_edit->line_buf = line_buf;
    line_edit->pos = 0;
    line_edit->is_eof = my_feof(MY_STDIN);
    return 0;
}

void sh_line_edit_update(sh_line_edit_t *line_edit)
{
    size_t back_steps = line_edit->line_buf->length - line_edit->pos;
    char back_buff[back_steps];

    printf("%c[2K$> ", 27);
    my_printf("Ok\n");
    my_puts(line_edit->line_buf->data);
    my_printf("Ok\n");
    for (size_t i = 0; i < back_steps; i++) {
        my_printf("Id %lu\n", i);
        back_buff[i] = '\b';
    }
    my_printf("Ok\n");
    write(STDOUT_FILENO, back_buff, back_steps);
}