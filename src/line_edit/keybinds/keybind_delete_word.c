/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** keybind_delete_word
*/

#include "token.h"
#include "line_edit.h"

int sh_keybind_delete_next_word(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c)
{
    char *line_str = line->data;
    size_t word_start = line_edit->pos;
    size_t word_end;

    (void)stream;
    (void)c;
    while (word_start < line->length && sh_is_arg_sep(line_str[word_start]))
        word_start++;
    word_end = word_start;
    while (word_end < line->length && !sh_is_arg_sep(line_str[word_end]))
        word_end++;
    my_vec_remove_multiple(
        line, NULL, line_edit->pos, word_end - line_edit->pos);
    sh_line_edit_update(line_edit, line);
    return 0;
}
