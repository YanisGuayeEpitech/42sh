/*
** EPITECH PROJECT, 2020
** LibMy - io module
** File description:
** Reads the contents of the standard input
*/

#include "libmy/core.h"
#include "libmy/io.h"
#include "libmy/collections.h"
#include <unistd.h>
#include <stdlib.h>

static size_t read_to_vec(my_vec_t *vec, size_t to_read, my_iostream_t *stream)
{
    size_t min_capacity = to_read + vec->length + 1;
    size_t read;

    if (min_capacity > vec->capacity) {
        size_t new_capacity = MY_MAX(min_capacity, vec->capacity * 2);

        if (my_vec_set_capacity(vec, new_capacity, NULL))
            return 0;
    }
    read = my_fread(((char *)vec->data) + vec->length, 1, to_read, stream);
    vec->length += read;
    ((char *)vec->data)[vec->length] = '\0';
    return read;
}

MY_API char *my_fread_to_string(size_t count, size_t *output_len,
my_iostream_t *stream)
{
    my_vec_t output;

    my_vec_init(&output, sizeof(char));
    *output_len = 0;
    if (my_vec_push(&output, ""))
        return NULL;
    output.length = 0;
    while (output.length < count) {
        size_t read = read_to_vec(&output, count - output.length, stream);

        if (read > 0)
            continue;
        if (my_feof(stream))
            break;
        my_vec_free(&output, NULL);
        return NULL;
    }
    *output_len = output.length;
    return (char *)(output.data);
}
