/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Tests the local variables functions
*/

#include <criterion/criterion.h>
#include "shell.h"

Test(sh_var_set, read_write_var)
{
    sh_ctx_t ctx;
    char const *argv[] = {"42sh", NULL};
    char *envp[] = {"PATH=/usr/bin", NULL};
    sh_lstr_t value;

    cr_assert_eq(sh_ctx_init(&ctx, 1, argv, envp), 0);
    cr_assert_eq(
        sh_var_set(&ctx, SH_LSTR("shell", 5), SH_LSTR("42sh", 4), false),
        SH_OK);
    value = sh_var_get(&ctx, SH_LSTR("shell", 5));
    cr_assert_eq(value.length, 4);
    cr_assert(my_memcmp(value.value, "42sh", 4) == 0);
    sh_ctx_drop(&ctx);
}

Test(sh_var_set, read_only_var)
{
    sh_ctx_t ctx;
    char const *argv[] = {"42sh", NULL};
    char *envp[] = {"PATH=/usr/bin", NULL};
    sh_lstr_t value;

    cr_assert_eq(sh_ctx_init(&ctx, 1, argv, envp), 0);
    cr_assert_eq(
        sh_var_set(&ctx, SH_LSTR("shell", 5), SH_LSTR("42sh", 4), true),
        SH_OK);
    cr_assert_eq(
        sh_var_set(&ctx, SH_LSTR("shell", 5), SH_LSTR("42sh", 4), true),
        SH_READ_ONLY_VAR);
    value = sh_var_get(&ctx, SH_LSTR("shell", 5));
    cr_assert_eq(value.length, 4);
    cr_assert(my_memcmp(value.value, "42sh", 4) == 0);
    sh_ctx_drop(&ctx);
}

Test(sh_var_remove, not_found)
{
    sh_ctx_t ctx;
    char const *argv[] = {"42sh", NULL};
    char *envp[] = {"PATH=/usr/bin", NULL};
    sh_lstr_t value;

    cr_assert_eq(sh_ctx_init(&ctx, 1, argv, envp), 0);
    cr_assert_eq(sh_var_remove(&ctx, SH_LSTR("shell", 5)), SH_OK);
    value = sh_var_get(&ctx, SH_LSTR("shell", 5));
    cr_assert_eq(value.length, 0);
    cr_assert_eq(value.value, NULL);
    sh_ctx_drop(&ctx);
}

Test(sh_var_remove, read_write_var)
{
    sh_ctx_t ctx;
    char const *argv[] = {"42sh", NULL};
    char *envp[] = {"PATH=/usr/bin", NULL};
    sh_lstr_t value;

    cr_assert_eq(sh_ctx_init(&ctx, 1, argv, envp), 0);
    cr_assert_eq(
        sh_var_set(&ctx, SH_LSTR("shell", 5), SH_LSTR("42sh", 4), false),
        SH_OK);
    cr_assert_eq(sh_var_remove(&ctx, SH_LSTR("shell", 5)), SH_OK);
    value = sh_var_get(&ctx, SH_LSTR("shell", 5));
    cr_assert_eq(value.length, 0);
    cr_assert_eq(value.value, NULL);
    sh_ctx_drop(&ctx);
}

Test(sh_var_remove, read_only_var)
{
    sh_ctx_t ctx;
    char const *argv[] = {"42sh", NULL};
    char *envp[] = {"PATH=/usr/bin", NULL};
    sh_lstr_t value;

    cr_assert_eq(sh_ctx_init(&ctx, 1, argv, envp), 0);
    cr_assert_eq(
        sh_var_set(&ctx, SH_LSTR("shell", 5), SH_LSTR("42sh", 4), true),
        SH_OK);
    cr_assert_eq(sh_var_remove(&ctx, SH_LSTR("shell", 5)), SH_READ_ONLY_VAR);
    value = sh_var_get(&ctx, SH_LSTR("shell", 5));
    cr_assert_eq(value.length, 4);
    cr_assert(my_memcmp(value.value, "42sh", 4) == 0);
    sh_ctx_drop(&ctx);
}
