/*
** EPITECH PROJECT, 2021
** LibMy - io module
** File description:
** Opens a file stream
*/

#include "my_fopen.h"
#include "libmy/io/iostream.h"

static int my_fopen_get_mode(const char *mode_str, int *invalid_mode)
{
    int plus = mode_str[0] != '\0' && mode_str[1] == '+';

    switch (*mode_str) {
        case 'r': return plus ? P_MY_FOPEN_R_PLUS : P_MY_FOPEN_R;
        case 'w': return plus ? P_MY_FOPEN_W_PLUS : P_MY_FOPEN_W;
        case 'a': return plus ? P_MY_FOPEN_A_PLUS : P_MY_FOPEN_A;
        default: *invalid_mode = 1; return 0;
    }
}

MY_IO_API int my_fopen(
    const char *path, const char *mode_str, my_iostream_t *stream)
{
    int invalid_mode = 0;
    int mode = my_fopen_get_mode(mode_str, &invalid_mode);
    int ret;

    if (invalid_mode)
        return 2;
    ret = open(path, mode);
    if (ret < 0)
        return 3;
    ret = my_finit_input_fd(ret, stream);
    if (ret != 0)
        my_fclose(stream);
    return ret;
}
