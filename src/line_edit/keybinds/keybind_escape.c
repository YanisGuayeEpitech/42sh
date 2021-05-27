/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** keybind_escape
*/

#include "line_edit.h"

static int sh_keybind_arrow(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c)
{
    char next_c;

    (void)c;
    if (my_fread(&next_c, sizeof(char), 1, stream) != 1)
        return -1;
    switch (next_c) {
        case 'D':
            return sh_keybind_move_left(line_edit, line, stream, &next_c);
        case 'C':
            return sh_keybind_move_right(line_edit, line, stream, &next_c);
        default: return 0;
    }
}

static void init_escape_keybinds(keybind_t keybinds[256])
{
    for (int i = 0; i < 256; i++)
        keybinds[i] = &sh_keybind_empty;
    keybinds[66] = &sh_keybind_backward_word;
    keybinds[67] = &sh_keybind_capitalize_word;
    keybinds[68] = &sh_keybind_delete_next_word;
    keybinds[70] = &sh_keybind_forward_word;
    keybinds[76] = &sh_keybind_downcase_word;
    keybinds[85] = &sh_keybind_upcase_word;
    keybinds[91] = &sh_keybind_arrow;
    keybinds[98] = &sh_keybind_backward_word;
    keybinds[99] = &sh_keybind_capitalize_word;
    keybinds[100] = &sh_keybind_delete_next_word;
    keybinds[102] = &sh_keybind_forward_word;
    keybinds[108] = &sh_keybind_downcase_word;
    keybinds[117] = &sh_keybind_upcase_word;
    keybinds[127] = &sh_keybind_delete_backward_word;
}

int sh_keybind_escape(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c)
{
    static keybind_t escape_sequence[256] = {NULL};
    char next_c;

    (void)c;
    if (my_fread(&next_c, sizeof(char), 1, stream) != 1)
        return -1;
    if (escape_sequence[0] == NULL)
        init_escape_keybinds(escape_sequence);
    return (*escape_sequence[(unsigned char)(next_c)])(line_edit, line, stream,
        &next_c);
}
