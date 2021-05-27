/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** keybinds
*/

#include <glob.h>
#include <libmy/ascii.h>
#include <unistd.h>

#include "line_edit.h"

static void init_keybinds(keybind_t keybinds[256])
{
    for (int i = 0; i < 256; i++)
        keybinds[i] =
            (my_isprint(i) || i > 127) ? &sh_keybind_show : &sh_keybind_empty;
    keybinds[9] = &sh_keybind_complete;
    keybinds[1] = &sh_keybind_line_start;
    keybinds[2] = &sh_keybind_move_left;
    keybinds[4] = &sh_keybind_eof;
    keybinds[5] = &sh_keybind_line_end;
    keybinds[6] = &sh_keybind_move_right;
    keybinds[8] = &sh_keybind_delete;
    keybinds[9] = &sh_keybind_tty_complete;
    keybinds[11] = &sh_keybind_line_kill_after_cursor;
    keybinds[12] = &sh_keybind_clear_screen;
    keybinds[21] = &sh_keybind_line_kill;
    keybinds[23] = &sh_keybind_line_kill_before_cursor;
    keybinds[127] = &sh_keybind_delete;
    keybinds['\n'] = &sh_keybind_send_cmd;
    keybinds[27] = &sh_keybind_escape;
}

int sh_exec_keybind(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c)
{
    static keybind_t keybinds[256] = {NULL};
    int code;

    if (!keybinds[0])
        init_keybinds(keybinds);
    code = (*keybinds[(unsigned char)(*c)])(line_edit, line, stream, c);
    return code;
}
