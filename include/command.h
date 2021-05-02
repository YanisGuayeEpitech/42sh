/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Command type definition
*/

#ifndef __SHELL_COMMAND_H__
#define __SHELL_COMMAND_H__

#include "builtin.h"
#include "token.h"

typedef enum sh_pipe_pos {
    SH_PIPE_BEGIN,
    SH_PIPE_MIDDLE,
    SH_PIPE_END,
    SH_PIPE_INVALID,
} sh_pipe_pos_t;

typedef enum sh_command_type {
    SH_COMMAND_UNRESOLVED,
    SH_COMMAND_EXTERNAL,
    SH_COMMAND_BUILTIN,
    SH_COMMAND_NOT_FOUND,
    SH_COMMAND_TYPE_COUNT,
} sh_command_type_t;

typedef struct sh_command_base {
    sh_command_type_t command_type;
    my_vec_t args;
    sh_pipe_pos_t pipe_pos;
    /// The path of the input redirection, set to @c NULL if no redirection.
    char const *input;
    /// The path of the output redirection, set to @c NULL if no redirection.
    char const *output;
    int input_fd;
    int output_fd;
    bool truncate;
} sh_command_base_t;

typedef struct sh_builtin_command {
    sh_command_base_t base;
    sh_builtin_t const *builtin;
} sh_builtin_command_t;

typedef struct sh_external_command {
    sh_command_base_t base;
    char const *path;
} sh_external_command_t;

typedef union sh_command {
    sh_command_type_t command_type;
    sh_command_base_t base;
    sh_builtin_command_t builtin;
    sh_external_command_t external;
} sh_command_t;

void sh_command_init(sh_command_t *command);

void sh_command_reset(sh_command_t *command);

void sh_command_drop(sh_command_t *command);

int sh_command_parse(sh_command_t *command, size_t token_count,
    sh_token_t tokens[], sh_pipe_pos_t pipe_pos);

bool sh_command_resolve(sh_ctx_t *ctx, sh_command_t *command);

int sh_command_execute(
    sh_ctx_t *ctx, sh_command_t *command, sh_command_t const *next_command);

int sh_execute_external(sh_ctx_t *ctx, char const *path, char const *argv[],
    sh_pipe_pos_t pipe_pos);
int sh_execute_builtin(sh_builtin_t const *builtin, sh_ctx_t *ctx, size_t argc,
    char const *argv[]);

int sh_external_pipe_setup(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2]);
int sh_external_pipe_dup(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2]);
int sh_external_pipe_close(
    sh_ctx_t *ctx, sh_pipe_pos_t pipe_pos, int old_pipe_fd[2]);

#endif // !defined(__SHELL_COMMAND_H__)
