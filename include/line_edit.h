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

struct sh_ctx_s;

typedef struct sh_line_edit_s {
    my_vec_t *line_buf;
    char *prompt;
    size_t pos;
    bool is_eof;
    struct sh_ctx_s *ctx;
} sh_line_edit_t;

int sh_line_edit_reset(
    struct sh_ctx_s *ctx, sh_line_edit_t *line_edit, my_vec_t *line_buf);
ssize_t sh_line_edit_fill(sh_line_edit_t *line_edit, my_iostream_t *stream);
void sh_line_edit_update(sh_line_edit_t *line_edit, my_vec_t *line_buf);

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
/// @brief Similar to sh_keybind_show but instead of inserting a char, it
/// remove the one at the pos line_edit->pos
///
/// @param line_edit The line_edit struct to keep the position of the cursor.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_delete(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Move the cursor to the left, decrement line_edit->pos
///
/// @param line_edit The line_edit struct to keep the position of the cursor.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_move_left(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Move the cursor to the right, increment line_edit->pos
///
/// @param line_edit The line_edit struct to keep the position of the cursor.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_move_right(
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
/// @brief Raise the end of the command
///
/// @param line_edit The line_edit struct. Not used here
/// @param line The line vector, a char * vector. A newline is pushed to this
/// vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised the end of the stream. Not used
/// here.
/// @return int
///
int sh_keybind_send_cmd(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Start an escape sequence.
///
/// @param line_edit The line_edit struct. Send to the next keybind.
/// @param line The line vector, a char * vector. A newline is pushed to this
/// vector. Send to the next keybind.
/// @param stream The stream from which the char was read. Send to the next
/// keybind to read the next char from the sequence.
/// @param c A pointer to the char which raised the end of the stream. Send to
/// the next keybind. here.
/// @return int
///
int sh_keybind_escape(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Set the cursor at the beginning of the line
///
/// @param line_edit The line_edit struct, to keep track of the cursor.
/// @param line The line vector, a char * vector. Not used here.
/// @param stream The stream from which the char was read. Not used here.
/// @param c  A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_line_start(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Set the cursor at the end of the line.
///
/// @param line_edit The line_edit struct, to keep track of the cursor.
/// @param line The line vector, a char * vector. Not used here.
/// @param stream The stream from which the char was read. Not used here.
/// @param c  A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_line_end(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Clear the characters before the cursor and set the cursor position
/// at the beginning of the line.
///
/// @param line_edit The line_edit struct, to keep track of the cursor.
/// @param line The line vector, a char * vector. Will be part cleared.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_line_kill_before_cursor(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Clear the characters after the cursor.
///
/// @param line_edit The line_edit struct, to keep track of the cursor.
/// @param line The line vector, a char * vector. Will be part cleared.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_line_kill_after_cursor(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Clear the line and set the cursor position at the beginning of the
/// line
///
/// @param line_edit The line_edit struct, to keep track of the cursor.
/// @param line The line vector, a char * vector. Will be cleared.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_line_kill(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Clear all the screen except the current line
///
/// @param line_edit The line_edit struct.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_clear_screen(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Delete the first word found after the cursor.
///
/// @param line_edit The line_edit struct.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_delete_next_word(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Move the cursor to the beginning of the last word.
///
/// @param line_edit The line_edit struct.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_backward_word(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Move the cursor to the end of the next word.
///
/// @param line_edit The line_edit struct.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_forward_word(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Capitalize the first word seen after the cursor (start at the cursor
/// position) and move the cursor at the end of this word
///
/// @param line_edit The line_edit struct.
/// @param line The line vector, a char * vector.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used here.
/// @return int
///
int sh_keybind_capitalize_word(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

///
/// @brief Does nothing, used for undefined keybinds.
///
/// @param line_edit The line_edit struct. Not used here.
/// @param line The line vector, a char * vector. Not used here.
/// @param stream The stream from which the char was read. Not used here.
/// @param c A pointer to the char which raised this call. Not used
/// here.
/// @return int
///
int sh_keybind_empty(
    sh_line_edit_t *line_edit, my_vec_t *line, my_iostream_t *stream, char *c);

#endif /* !LINE_EDITION_H_ */