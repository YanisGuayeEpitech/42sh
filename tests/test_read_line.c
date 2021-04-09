/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Tests the sh_read_line function
*/

#include <libmy/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

static void setup(void)
{
    my_init_stdin(malloc(256), 256, &free);
}

static void finish(void)
{
    my_free_stdin();
}

Test(sh_read_line, closed_stdin, .init = &setup, .fini = &finish)
{
    sh_ctx_t ctx;
    char *envp[] = {NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    fclose(stdin);
    cr_assert_eq(sh_read_line(&ctx), -1);
    sh_ctx_drop(&ctx);
}

Test(sh_read_line, empty_line, .init = &setup, .fini = &finish)
{
    FILE *in = cr_get_redirected_stdin();
    sh_ctx_t ctx;
    char *envp[] = {NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    fputc('\n', in);
    fflush(in);
    cr_assert_eq(sh_read_line(&ctx), 1);
    cr_assert_eq(ctx.line_buf.length, 0);
    cr_assert_geq(ctx.line_buf.capacity, 2);
    cr_assert_str_eq(ctx.line_buf.data, "\n");
    sh_ctx_drop(&ctx);
}

Test(sh_read_line, multi_line, .init = &setup, .fini = &finish)
{
    FILE *in = cr_get_redirected_stdin();
    sh_ctx_t ctx;
    char *envp[] = {NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    fputs("This is a test\n", in);
    fflush(in);
    cr_assert_eq(sh_read_line(&ctx), 15);
    cr_assert_eq(ctx.line_buf.length, 14);
    cr_assert_geq(ctx.line_buf.capacity, 16);
    cr_assert_str_eq(ctx.line_buf.data, "This is a test\n");
    fputs("yeast\n", in);
    fflush(in);
    cr_assert_eq(sh_read_line(&ctx), 6);
    cr_assert_eq(ctx.line_buf.length, 5);
    cr_assert_geq(ctx.line_buf.capacity, 16);
    cr_assert_str_eq(ctx.line_buf.data, "yeast\n");
    fclose(stdin);
    cr_assert_eq(sh_read_line(&ctx), -1);
    sh_ctx_drop(&ctx);
}
