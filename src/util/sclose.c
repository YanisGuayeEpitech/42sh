/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Closes a file descriptor and sets it to -1
*/

#include <assert.h>
#include <unistd.h>

int sh_sclose(int *fd)
{
    int ret;

    assert(fd != NULL);
    if (*fd == -1)
        return 0;
    ret = close(*fd);
    *fd = -1;
    return ret;
}
