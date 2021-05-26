/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** keybinds
*/

#include <libmy/ascii.h>

#include "line_edit.h"

static void init_keybinds(keybind_t keybinds[256])
{
    for (int i = 0; i < 256; i++) {
        if (my_isprint(i) || i > 127)
            keybinds[i] = &sh_keybind_show;
        else
            keybinds[i] = &sh_keybind_empty;
    }
    keybinds[4] = &sh_keybind_eof;
    keybinds[127] = &sh_keybind_delete;
    keybinds['\n'] = &sh_keybind_send_cmd;
    keybinds['L'] = &sh_keybind_move_left;
    keybinds['R'] = &sh_keybind_move_right;
}

int sh_exec_keybind(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c)
{
    static keybind_t keybinds[256] = {NULL};
    int code;

    if (!keybinds[(int)(*c)])
        init_keybinds(keybinds);
    code = (*keybinds[(int)(*c)])(line_edit, line, stream, c);
    return code;
}
