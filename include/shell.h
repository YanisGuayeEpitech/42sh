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

#endif // !defined(__SHELL_H__)
