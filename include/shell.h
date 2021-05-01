/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** The main header file$
*/

#ifndef __SHELL_H__
#define __SHELL_H__

#include <sys/types.h>

#include "context.h"
#include "error.h"
#include "input.h"

#define IO_BUF_SIZE (1024)

/// Starts the shell.
///
/// @param ctx The shell context.
void sh_start(sh_ctx_t *ctx);

bool sh_lint_tokens(size_t token_count, sh_token_t tokens[token_count]);

int sh_exec_parse(
    sh_ctx_t *ctx, size_t token_count, sh_token_t tokens[token_count]);

typedef enum sh_pipe_pos {
    SH_PIPE_BEGIN,
    SH_PIPE_MIDDLE,
    SH_PIPE_END,
} sh_pipe_pos_t;

int sh_exec_tokens(sh_ctx_t *ctx, size_t token_count,
    sh_token_t tokens[token_count], sh_pipe_pos_t pipe_pos);

/// Executes the given line.
///
/// @param ctx The shell context.
/// @param argc The number of arguments, excluding the null terminator, always
/// greater than zero.
/// @param argv A null-terminated list of arguments, should contain at least
/// one argument.
/// @param pipe_pos Where this command is located in the pipe chain.
///
/// @returns A negative value if the shell should exit.
int sh_exec(
    sh_ctx_t *ctx, size_t argc, char const *argv[], sh_pipe_pos_t pipe_pos);

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

/// Finds an executable named @c to_find in one of directories listed in $PATH.
///
/// @param ctx The shell context.
/// @param to_find The executable to find.
///
/// @returns The full path of the executable if found, or @c NULL otherwise.
char *sh_find_executable(sh_ctx_t *ctx, char const *to_find);

/// Fetches an environment variable entry with the given key and key size.
///
/// @param ctx The shell context.
/// @param key The key.
/// @param key_len The number of characters in @c key.
///
/// @returns A pointer to the full entry string, @c NULL if no entry was found.
char **sh_env_get_entry(sh_ctx_t *ctx, char const *key, size_t key_len);

/// Adds or updates and environment variable with the given key and value.
///
/// @param ctx The shell context.
/// @param key The name of the variable.
/// @param value The value of the variable.
void sh_env_set(sh_ctx_t *ctx, char const *key, char const *value);

/// Removes an environment variable named @c key.
///
/// @param ctx The shell context.
/// @param key The name of the variable.
///
/// @returns 1 if the variable was found and removed, 0 otherwise.
int sh_env_remove(sh_ctx_t *ctx, char const *key);

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

/// Fetches the current working directory's absolute path.
///
/// @returns The current working directory.
char *sh_get_cwd(void);

int sh_external_pipe_setup(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2]);
int sh_external_pipe_dup(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2]);
int sh_external_pipe_close(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2]);
#endif // !defined(__SHELL_H__)
