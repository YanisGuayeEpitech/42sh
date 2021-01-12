/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_get_std* functions
*/

#include <criterion/criterion.h>
#include "libmy/io.h"

Test(my_get_stdin, base)
{
    cr_assert_neq(my_get_stdin(), NULL);
    cr_assert_neq(MY_STDIN, NULL);
}

Test(my_get_stdout, base)
{
    cr_assert_neq(my_get_stdout(), NULL);
    cr_assert_neq(MY_STDOUT, NULL);
}

Test(my_get_stderr, base)
{
    cr_assert_neq(my_get_stderr(), NULL);
    cr_assert_neq(MY_STDERR, NULL);
}
