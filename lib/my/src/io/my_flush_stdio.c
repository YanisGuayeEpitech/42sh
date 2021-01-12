/*
** EPITECH PROJECT, 2020
** LibMy - io module
** File description:
** Flushes the standard streams
*/

#include "libmy/io.h"

int my_flush_stdin(void)
{
    return my_fflush(MY_STDIN);
}

int my_flush_stdout(void)
{
    return my_fflush(MY_STDOUT);
}

int my_flush_stderr(void)
{
    return my_fflush(MY_STDERR);
}
