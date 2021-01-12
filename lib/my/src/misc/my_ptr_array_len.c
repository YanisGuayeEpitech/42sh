/*
** EPITECH PROJECT, 2020
** LibMy - misc module
** File description:
** Computes the length of a null-terminated string array
*/

#include "libmy/misc.h"

MY_API int my_ptr_array_len(void const *array[])
{
    int len = 0;

    if (!array)
        return 0;
    while (array[len])
        ++len;
    return len;
}
