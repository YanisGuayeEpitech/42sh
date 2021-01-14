/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** The main header file$
*/

#ifndef __SHELL_H__
#define __SHELL_H__

#include <libmy/collections.h>

#define IO_BUF_SIZE (1024)

typedef struct {
    my_vec_t env;
    /// The index of the 'PATH' variable in env, or @c SIZE_MAX if not present.
    size_t path_index;
    int is_tty;
} sh_ctx_t;

/// Initializes the shell's context
///
/// @param envp A NULL-terminared array of strings.
///
/// @returns 0 if successful.
int sh_ctx_init(sh_ctx_t *ctx, char **envp);

/// Frees the contents of the shell context.
///
/// @param ctx The shell context.
void sh_ctx_drop(sh_ctx_t *ctx);

/// Starts the shell.
///
/// @param ctx The shell context.
void sh_start(sh_ctx_t *ctx);

/// Executes the given line.
///
/// @param ctx The shell context.
/// @param line The line to execute.
int sh_exec(sh_ctx_t *ctx, char *line);

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

#endif // !defined(__SHELL_H__)
