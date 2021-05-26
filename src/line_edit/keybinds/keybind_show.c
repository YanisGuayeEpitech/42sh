/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** keybind_show
*/

#include "line_edit.h"

int sh_keybind_show(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c)
{
    (void)line_edit;
    (void)stream;
    return my_vec_push(line, c);
}
