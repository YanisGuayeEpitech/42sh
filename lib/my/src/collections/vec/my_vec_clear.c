/*
** EPITECH PROJECT, 2021
** LibMy - collections module
** File description:
** Flushes the elements of a vector
*/

#include "libmy/collections/vec.h"

MY_COLLECTIONS_API void my_vec_clear(my_vec_t *vec, void (*elem_free)(void *))
{
    assert(vec != NULL);
    if (elem_free != NULL) {
        size_t len = vec->length;

        for (size_t i = 0; i < len; ++i)
            (*elem_free)(my_vec_get(vec, i));
    }
    vec->length = 0;
}
