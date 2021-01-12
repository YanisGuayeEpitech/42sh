/*
** EPITECH PROJECT, 2020
** LibMy - io module
** File description:
** Retrieves the standard streams
*/

#include "libmy/io.h"

my_fstream_t *my_get_stdin(void)
{
    static my_fstream_t my_stdin;

    return &my_stdin;
}

my_fstream_t *my_get_stdout(void)
{
    static my_fstream_t my_stdout;

    return &my_stdout;
}

my_fstream_t *my_get_stderr(void)
{
    static my_fstream_t my_stderr;

    return &my_stderr;
}
