/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** The main header file$
*/

#ifndef __SHELL_H__
#define __SHELL_H__

#include <sys/types.h>

#include "context.h"
#include "error.h"
#include "token.h"

#define IO_BUF_SIZE (1024)

/// Parses the arguments.
///
/// @returns Whether the shell should start.
bool sh_parse_args(sh_ctx_t *ctx, int ac, char *av[]);

/// Starts the shell.
///
/// @param ctx The shell context.
void sh_start(sh_ctx_t *ctx);

sh_error_t sh_lint(size_t token_count, sh_token_t tokens[token_count]);

int sh_execute(
    sh_ctx_t *ctx, size_t token_count, sh_token_t tokens[token_count]);

int sh_handle_status(sh_ctx_t *ctx, int status);

/// Prints the passed message only if stdin is a tty.
///
/// @param ctx The shell context.
/// @param msg The line to print
void sh_print(sh_ctx_t *ctx, char const *msg);

/// Prints the shell prompt if stdin is a tty.
///
/// @param ctx The shell context.
void sh_print_prompt(sh_ctx_t *ctx);

/// Fetches an environment variable entry with the given key and key size.
///
/// @param ctx The shell context.
/// @param key The key.
/// @param key_len The number of characters in @c key.
///
/// @returns A pointer to the full entry string, @c NULL if no entry was found.
char **sh_env_get_entry(sh_ctx_t *ctx, sh_lstr_t key);

/// Adds or updates and environment variable with the given key and value.
///
/// @param ctx The shell context.
/// @param key The name of the variable.
/// @param value The value of the variable.
void sh_env_set(sh_ctx_t *ctx, sh_lstr_t key, sh_lstr_t value);

/// Removes an environment variable named @c key.
///
/// @param ctx The shell context.
/// @param key The name of the variable.
///
/// @returns @c true if the variable was found and removed, @c false otherwise.
bool sh_env_remove(sh_ctx_t *ctx, sh_lstr_t key);

sh_lstr_t sh_var_get(sh_ctx_t *ctx, sh_lstr_t key);

sh_error_t sh_var_set(
    sh_ctx_t *ctx, sh_lstr_t key, sh_lstr_t value, bool read_only);

sh_error_t sh_var_remove(sh_ctx_t *ctx, sh_lstr_t value);

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

/// Fetches the current working directory's absolute path.
///
/// @returns The current working directory.
char *sh_get_cwd(void);

bool sh_open_script(sh_ctx_t *ctx, char const *path);

#endif // !defined(__SHELL_H__)
