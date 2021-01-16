/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** The main header file$
*/

#ifndef __SHELL_H__
#define __SHELL_H__

#include "context.h"

#define IO_BUF_SIZE (1024)

typedef enum {
    SH_OK = 0,
    SH_EXPRESSION_SYNTAX,
    SH_BAD_NUMBER,
    SH_BAD_VAR_START,
    SH_BAD_VAR_CHARS,
    SH_ERROR_MAX,
} sh_error_t;

/// Retrurns a string corresponding to the given error code.
///
/// @param code The error code.
///
/// @returns The error string, or "Unknown error" if <tt>code < SH_OK</tt> or
/// <tt>code >= SH_ERROR_MAX</tt>.
char const *sh_strerror(sh_error_t code);

/// Prints the given error code to the standard error output.
///
/// Does nothing if @c code is @c SH_OK.
///
/// @param prefix If not null or empty, prefix is printed followed by a color
/// and a blank.
/// @param code The error code.
///
/// @returns The @c code argument.
sh_error_t sh_perror(char const *prefix, sh_error_t code);

/// Starts the shell.
///
/// @param ctx The shell context.
void sh_start(sh_ctx_t *ctx);

/// Executes the given line.
///
/// @param ctx The shell context.
/// @param line The line to execute.
int sh_exec(sh_ctx_t *ctx, char const *line);

/// Prints the passed message only if stdout is a tty.
///
/// @param ctx The shell context.
/// @param msg The line to print
void sh_print(sh_ctx_t *ctx, char const *msg);

/// Contatenates the given components, adding a '/' if necessary.
///
/// @param dir_len The length in bytes of @c dir_name
/// @param dir_name The directory part of the path
/// @param file_name The file part to add.
///
/// @returns The path, or NULL if allocation failed.
char *sh_create_file_path(
    size_t dir_len, char const *dir_name, char const *file_name);

/// Finds an executable named @c to_find in one of directories listed in $PATH.
///
/// @param ctx The shell context.
/// @param to_find The executable to find.
///
/// @returns The full path of the executable if found, or @c NULL otherwise.
char *sh_find_executable(sh_ctx_t *ctx, char const *to_find);

/// Frees an entry of a string pointer array.
///
/// For use with @c my_vec_free.
///
/// @param ptr The pointer to free.
void sh_free_entry(void *ptr);

/// Attempts to parse an int.
///
/// @param str The string to parse.
/// @param[out] result Where the parsed int is stored.
///
/// @returns @c SH_OK if the parsing succeded, or an error code otherwise.
sh_error_t sh_parse_int(char const *str, int *result);

/// Validates a variable name.
///
/// A valid variable name matches the regex [a-zA-Z_][a-zA-Z_0-9]*
///
/// @param name The variable name.
/// @param name_len The number of characters in @c name.
///
/// @returns @c SH_OK if @c name is a valid variable name, or an error code
/// otherwise.
sh_error_t sh_check_var_name(char const *name, size_t name_len);

#endif // !defined(__SHELL_H__)
