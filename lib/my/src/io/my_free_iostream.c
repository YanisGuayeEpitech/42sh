/*
** EPITECH PROJECT, 2020
** LibMy - io module
** File description:
** Frees the builtin streams
*/

#include "libmy/io.h"

MY_API void my_free_stdin(void)
{
    my_ffree(MY_STDIN);
}

MY_API void my_free_stdout(void)
{
    my_ffree(MY_STDOUT);
}

MY_API void my_free_stderr(void)
{
    my_ffree(MY_STDERR);
}
