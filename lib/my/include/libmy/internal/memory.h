/*
** EPITECH PROJECT, 2020
** LibMy - memory module internals
** File description:
** The internals for the memory module
*/

#ifndef __LIBMY_INTERNAL_MEMORY_H__
#define __LIBMY_INTERNAL_MEMORY_H__

#include "libmy/internal/attributes.h"

MY_API_BEGIN

#include "libmy/memory/cbuffer.h"

MY_INLINE size_t my_cbuffer_wrap_add(
    my_cbuffer_t const *buf, size_t index, size_t to_add)
{
    if (index >= buf->cap - to_add)
        return to_add - (buf->cap - index);
    else
        return index + to_add;
}

MY_INLINE size_t my_cbuffer_wrap_sub(
    my_cbuffer_t const *buf, size_t index, size_t to_sub)
{
    if (to_sub > index)
        return buf->cap + index - to_sub;
    else
        return index - to_sub;
}

MY_API_END

#endif // !defined(__LIBMY_INTERNAL_MEMORY_H__)
