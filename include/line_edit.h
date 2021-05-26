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

#include "definition.h"

typedef struct sh_line_edit_s {
    my_vec_t *line_buf;
    size_t pos;
    bool is_eof;
} sh_line_edit_t;

int sh_line_edit_reset(sh_line_edit_t *line_edit, my_vec_t *line_buf);
ssize_t sh_line_edit_fill(sh_line_edit_t *line_edit, my_iostream_t *stream);

typedef int (*keybind_t)(
    sh_line_edit_t *, my_vec_t *, my_iostream_t *, char *);
int sh_exec_keybind(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Insert the char c in the char * vector line at the position
/// line_edit->pos
///
/// @param line_edit The line_edit struct to keep the position of the cursor.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char that must be inserted.
/// @return int
///
int sh_keybind_show(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Raise the end of the stream
///
/// @param line_edit The line_edit struct, to keep the eof bool.
/// @param line The line vector, a char * vector. Not used here.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised the end of the stream. Not used
/// here.
/// @return int
///
int sh_keybind_eof(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Does nothing, used for undefined keybinds.
///
/// @param line_edit The line_edit struct. Not used here.
/// @param line The line vector, a char * vector. Not used here.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised the end of the stream. Not used
/// here.
/// @return int
///
int sh_keybind_empty(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

#endif /* !LINE_EDITION_H_ */