/*
** EPITECH PROJECT, 2021
** minishell1
** File description:
** Tests the parsing functions
*/

#include <criterion/criterion.h>
#include "shell.h"

Test(sh_check_var_name, invalid_start)
{
    cr_assert_eq(sh_check_var_name(NULL, 42), SH_BAD_VAR_START);
    cr_assert_eq(sh_check_var_name("yeet", 0), SH_BAD_VAR_START);
    cr_assert_eq(sh_check_var_name("!lel", 4), SH_BAD_VAR_START);
    cr_assert_eq(sh_check_var_name(" lel", 4), SH_BAD_VAR_START);
    cr_assert_eq(sh_check_var_name("~lel", 4), SH_BAD_VAR_START);
}

Test(sh_check_var_name, invalid_chars)
{
    cr_assert_eq(sh_check_var_name("f*rge", 5), SH_BAD_VAR_CHARS);
    cr_assert_eq(sh_check_var_name("f rge", 5), SH_BAD_VAR_CHARS);
    cr_assert_eq(sh_check_var_name("f~rge", 5), SH_BAD_VAR_CHARS);
}

Test(sh_check_var_name, valid_names)
{
    cr_assert_eq(sh_check_var_name("_", 1), SH_OK);
    cr_assert_eq(sh_check_var_name("_=/bin/sh", 1), SH_OK);
    cr_assert_eq(sh_check_var_name("asdf", 4), SH_OK);
    cr_assert_eq(sh_check_var_name("ASDF", 4), SH_OK);
    cr_assert_eq(sh_check_var_name("ThiSISAteST", 11), SH_OK);
    cr_assert_eq(sh_check_var_name("SSH_AGENT", 9), SH_OK);
}
