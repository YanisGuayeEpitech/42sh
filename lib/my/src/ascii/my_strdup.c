/*
** EPITECH PROJECT, 2020
** LibMy - ascii module
** File description:
** Duplicates the given string
*/

#include <stdlib.h>
#include "libmy/ascii.h"

MY_ASCII_API char *my_strdup(char const *src)
{
    char *dup;

    if (!src)
        return NULL;
    dup = malloc(sizeof(*dup) * (my_strlen(src) + 1));
    if (!dup)
        return NULL;
    my_strcpy(dup, src);
    return dup;
}
