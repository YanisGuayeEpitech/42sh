/*
** EPITECH PROJECT, 2020
** LibMy - memory module
** File description:
** Finds an element in a sorted array
*/

#include "libmy/memory.h"

MY_API void *my_binary_search(void * const array[], void const *to_find,
size_t len, int (*cmp)())
{
    if (!array || !cmp)
        return NULL;
    while (len != 0) {
        size_t mid = len / 2;
        int comparison = (*cmp)(to_find, array[mid]);

        if (comparison == 0)
            return (void *)(array + mid);
        if (comparison < 0) {
            len = mid;
            continue;
        } else if (mid + 1 >= len) {
            return NULL;
        }
        array += mid + 1;
        len -= mid + 1;
    }
    return NULL;
}
