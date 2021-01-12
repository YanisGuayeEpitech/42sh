/*
** EPITECH PROJECT, 2020
** LibMy - misc module
** File description:
** swaps the contents of the passed int pointers
*/

#include "libmy/misc.h"

MY_API void my_swap(int *a, int *b)
{
    if (a == b)
        return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
