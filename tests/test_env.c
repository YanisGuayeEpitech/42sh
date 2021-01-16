/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Tests the env functions
*/

#include <criterion/criterion.h>
#include "shell.h"

Test(sh_env_get_entry, not_found)
{
    sh_ctx_t ctx;
    char *envp[] = {"PATH=/usr/bin", "USER=root", NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    cr_assert_eq(sh_env_get_entry(&ctx, "SHELL", 5), NULL);
    sh_ctx_drop(&ctx);
}

Test(sh_env_get_entry, found)
{
    sh_ctx_t ctx;
    char *envp[] = {"PATH=/usr/bin", "USER=root", "SHELL=mysh", NULL};
    char **entry;

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    entry = sh_env_get_entry(&ctx, "SHELL", 5);
    cr_assert_neq(entry, NULL);
    cr_assert_str_eq(*entry, "SHELL=mysh");
    sh_ctx_drop(&ctx);
}

Test(sh_env_set, new_variable)
{
    sh_ctx_t ctx;
    char *envp[] = {"PATH=/usr/bin", "USER=root", NULL};
    char **entry;

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    sh_env_set(&ctx, "SHELL", "mysh");
    entry = sh_env_get_entry(&ctx, "SHELL", 5);
    cr_assert_neq(entry, NULL);
    cr_assert_str_eq(*entry, "SHELL=mysh");
    cr_assert_eq(ctx.env.length, 4);
    cr_assert_geq(ctx.env.capacity, 4);
    cr_assert_str_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 2), "SHELL=mysh");
    sh_ctx_drop(&ctx);
}

Test(sh_env_set, update_variable)
{
    sh_ctx_t ctx;
    char *envp[] = {"PATH=/usr/bin", "SHELL=zsh", "USER=root", NULL};
    char **entry;

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    sh_env_set(&ctx, "SHELL", "mysh");
    entry = sh_env_get_entry(&ctx, "SHELL", 5);
    cr_assert_neq(entry, NULL);
    cr_assert_str_eq(*entry, "SHELL=mysh");
    cr_assert_eq(ctx.env.length, 4);
    cr_assert_geq(ctx.env.capacity, 4);
    cr_assert_str_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 1), "SHELL=mysh");
    sh_ctx_drop(&ctx);
}

Test(sh_env_remove, not_found)
{
    sh_ctx_t ctx;
    char *envp[] = {"PATH=/usr/bin", "USER=root", NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    cr_assert_eq(sh_env_remove(&ctx, "SHELL"), 0);
    sh_ctx_drop(&ctx);
}

Test(sh_env_remove, found)
{
    sh_ctx_t ctx;
    char *envp[] = {"PATH=/bin", "USER=root", "SHELL=bash", NULL};

    cr_assert_eq(sh_ctx_init(&ctx, envp), 0);
    cr_assert_eq(sh_env_remove(&ctx, "SHELL"), 1);
    cr_assert_eq(sh_env_get_entry(&ctx, "SHELL", 5), NULL);
    cr_assert_eq(ctx.env.length, 3);
    cr_assert_eq(ctx.env.capacity, 3);
    cr_assert_str_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 0), "PATH=/bin");
    cr_assert_str_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 1), "USER=root");
    cr_assert_eq(MY_VEC_GET_ELEM(char *, &ctx.env, 2), NULL);
    sh_ctx_drop(&ctx);
}
