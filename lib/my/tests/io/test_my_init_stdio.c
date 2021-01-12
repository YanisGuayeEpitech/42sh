/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_init_std* functions
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "libmy/io.h"

Test(my_init_stdin, base)
{
    unsigned char buf[256];

    cr_assert_eq(my_init_stdin(buf, 256, NULL), 0);
    cr_assert_eq(MY_STDIN->buf, buf);
    cr_assert_eq(MY_STDIN->buf_cap, 256);
    cr_assert_eq(MY_STDIN->fd, 0);
    cr_assert_eq(MY_STDIN->is_eof, 0);
    cr_assert_eq(MY_STDIN->type, MY_STREAM_INPUT);
    cr_assert_eq(MY_STDOUT->free_buf, NULL);
}

Test(my_init_stdout, base)
{
    unsigned char buf[256];

    cr_assert_eq(my_init_stdout(buf, 256, NULL), 0);
    cr_assert_eq(MY_STDOUT->buf, buf);
    cr_assert_eq(MY_STDOUT->buf_cap, 256);
    cr_assert_eq(MY_STDOUT->fd, 1);
    cr_assert_eq(MY_STDOUT->is_eof, 0);
    cr_assert_eq(MY_STDOUT->type, MY_STREAM_OUTPUT);
    cr_assert_eq(MY_STDOUT->free_buf, NULL);
}

Test(my_init_stderr, base)
{
    unsigned char buf[256];

    cr_assert_eq(my_init_stderr(buf, 256, &free), 0);
    cr_assert_eq(MY_STDERR->buf, buf);
    cr_assert_eq(MY_STDERR->buf_cap, 256);
    cr_assert_eq(MY_STDERR->fd, 2);
    cr_assert_eq(MY_STDERR->is_eof, 0);
    cr_assert_eq(MY_STDERR->type, MY_STREAM_OUTPUT);
    cr_assert_eq(MY_STDERR->free_buf, &free);
}
