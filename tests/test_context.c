/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Tests the shell context functions
*/

#include <criterion/criterion.h>
#include "shell.h"

Test(sh_ctx_init, empty_env)
{
    sh_ctx_t ctx;
    char *envp[] = {NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    cr_assert_eq(ctx.env.capacity, 1);
    cr_assert_eq(ctx.env.length, 1);
    cr_assert_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 0), NULL);
}

Test(sh_ctx_init, normal_env)
{
    sh_ctx_t ctx;
    char *envp[] = {"PATH=/bin", "USER=yeet", NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    cr_assert_eq(ctx.env.capacity, 3);
    cr_assert_eq(ctx.env.length, 3);
    cr_assert_str_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 0), "PATH=/bin");
    cr_assert_str_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 1), "USER=yeet");
    cr_assert_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 2), NULL);
}

Test(sh_ctx_drop, normal)
{
    sh_ctx_t ctx;
    char *envp[] = {"PATH=/usr/bin", "USER=root", NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    sh_ctx_drop(&ctx);
}