/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Executes a token array
*/

#include "command.h"
#include "shell.h"

static sh_command_t *sh_pipeline_push(sh_ctx_t *ctx)
{
    sh_command_t *command;

    if (my_vec_reserve(&ctx->pipeline, 1) != MY_VEC_OK)
        return NULL;
    command = my_vec_get(&ctx->pipeline, ctx->pipeline.length++);
    sh_command_init(command);
    return command;
}

static int sh_pipeline_execute(sh_ctx_t *ctx)
{
    int ret = 0;
    size_t len = ctx->pipeline.length;
    sh_command_t *command;

    for (size_t i = 0; i < len; ++i)
        sh_command_resolve(ctx, my_vec_get(&ctx->pipeline, i));
    for (size_t i = 0; i < len; ++i) {
        command = my_vec_get(&ctx->pipeline, i);
        ret = sh_command_execute(ctx, command,
            i + 1 < len ? my_vec_get(&ctx->pipeline, i + 1) : NULL);
        if (ret != 0)
            break;
    }
    my_vec_clear(&ctx->pipeline, (void (*)(void *))(&sh_command_drop));
    return ret;
}

static int sh_exec_parse_pipes(
    sh_ctx_t *ctx, size_t tcount, sh_token_t tokens[tcount])
{
    size_t end;
    int ret;
    sh_pipe_pos_t pipe_pos = SH_PIPE_BEGIN;

    while (tcount > 0) {
        end = sh_token_find(tcount, tokens, SH_TOKEN_PIPE);
        ret = sh_command_parse(sh_pipeline_push(ctx), end, tokens,
            end == tcount ? SH_PIPE_END : pipe_pos);
        if (ret != 0)
            return ret;
        sh_token_advance(&tcount, &tokens, end);
        pipe_pos = SH_PIPE_MIDDLE;
        sh_token_consume(&tcount, &tokens, SH_TOKEN_PIPE);
    }
    return sh_pipeline_execute(ctx);
}

static int sh_exec_parse_semicolons(
    sh_ctx_t *ctx, size_t token_count, sh_token_t tokens[token_count])
{
    size_t end;
    int ret;

    do {
        sh_token_consume_while(&token_count, &tokens, SH_TOKEN_SEMICOLON);
        end = sh_token_find(token_count, tokens, SH_TOKEN_SEMICOLON);
        ret = sh_exec_parse_pipes(ctx, end, tokens);
        if (ret != 0)
            return ret;
        sh_token_advance(&token_count, &tokens, end);
    } while (end != 0);
    return 0;
}

int sh_execute(
    sh_ctx_t *ctx, size_t token_count, sh_token_t tokens[token_count])
{
    sh_error_t err;
    int ret;

    err = sh_lint(token_count, tokens);
    if (err != SH_OK) {
        ctx->exit_code = 1;
        sh_perror(NULL, err);
        return ctx->is_tty ? 1 : -1;
    }
    ret = sh_exec_parse_semicolons(ctx, token_count, tokens);
    if (ret > 0)
        ctx->exit_code = 1;
    if (ctx->had_exit_cmd != -1) {
        ctx->exit_code = ctx->had_exit_cmd;
        return (-1);
    }
    return ret;
}
