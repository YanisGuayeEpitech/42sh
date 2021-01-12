/*
** EPITECH PROJECT, 2020
** LibMy - memory module
** File description:
** The main header for the memory module
*/

/// @file
///
/// Memory related utilities.
///
/// @since 0.1.0

#ifndef __LIBMY_MEMORY_H__
#define __LIBMY_MEMORY_H__

#include "libmy/internal/attributes.h"

MY_API_BEGIN

#ifndef LIBMY_MODULE_MEMORY
    #error "LibMy: 'libmy/memory.h' is included, \
but memory module is not present"
#endif

#include <stddef.h>
#include "libmy/memory/cbuffer.h"

#include "libmy/internal/memory.h"

/// Performs a binary search on a sorted pointer array.
///
/// @param array   The source array, must be sorted.
/// @param to_find The element to find in @c array.
/// @param len     The number of elements in @c array.
/// @param cmp     The comparison function,
///                takes @c to_find as the first parameter,
///                a pointer to the nth element in @c array
///                and returns an integer less than, equal to,
///                or greater than zero if @c to_find is found respectively
///                to be less than, to match, or be greater
///                than the second parameter.
///
/// @returns A pointer to the found element, or @c NULL if not found.
/// @since 0.1.0
MY_API void *my_binary_search(
    void *const array[], void const *to_find, size_t len, int (*cmp)());

/// Copies @c n bytes from @c src to @c dest.
///
/// @param[out] dest The destination memory, must be a valid address.
/// @param src       The source memory, must be a valid address.
/// @param n         The number of bytes to copy.
///
/// @returns The passed @c dest pointer.
/// @since 0.1.0
MY_API void *my_memcpy(void *dest, const void *src, size_t n);

/// Copies @c n bytes from @c src to @c dest.
/// The memory areas may overlap.
///
/// @param[out] dest The destination memory, must be a valid address.
/// @param src       The source memory, must be a valid address.
/// @param n         The number of bytes to copy.
///
/// @returns The passed @c dest pointer.
/// @since 0.1.0
MY_API void *my_memmove(void *dest, const void *src, size_t n);

/// Swaps the two passed pointers, @c a and @c b must not alias.
///
/// @param a Set to the value of @c b.
/// @param b Set to the valud of @c a.
///
/// @since 0.1.0
MY_API void my_swap_ptr(void const **restrict a, void const **restrict b);

/// Fills the first @c size bytes of the memory area pointed to by @c mem
/// with the constant byte @c byte.
///
/// @param mem  The memory location, can be @c NULL.
/// @param byte The byte to write.
/// @param size The number of bytes to fill.
///
/// @returns A pointer to the memory area @c mem.
MY_API void *my_memset(void *mem, unsigned char byte, size_t size);

#ifdef LIBMY_ALLOW_MALLOC
/// Changes the size of the memory pointed to by @c ptr from @c old_size
/// to @c new_size bytes.
/// The contents will be unchanged in the range from the start of the
/// region up to the minimum of the old and new sizes.
/// If @c new_size if larger than @c old_size, the added memory will @b not
/// be initialized.
/// If @c ptr is @c NULL then the call is equivalent to
/// <tt>malloc(new_size)</tt>.
/// If @c new_size if zero, and @c ptr is not @c NULL,
/// then the call is equivalent to <tt>free(ptr)</tt>.
///
/// @note
/// This function requires the @c alloc_malloc flag to be used.
///
/// @param ptr      A pointer to the memory block to resize.
/// @param old_size The current size of the memory block.
/// @param new_size The new size of the memory block.
///
/// @returns A pointer to the resized memory block.
/// @since 0.1.0
MY_API void *my_realloc(void *ptr, size_t old_size, size_t new_size);
#endif

/// The type of comparision function used by @ref my_msort.
///
/// This function is called passing as arguments pointers to
/// two array elements to be compared.
/// This function should return a value the way @c my_strcmp does.
///
/// @since 0.2.0
typedef int (*my_comparator_t)(void const *, void const *);

/// Sorts the given data using Merge Sort.
///
/// @param data  A pair of arrays,
///              the first one is the data to sort and the second one is
///              the buffer array.
/// @param nmemb The number of elements in @c data.
/// @param size  The size of an individual element of @c data.
/// @param cmp   The comparison function,
///              see @ref my_comparator_t for more detals.
///
/// @since 0.2.0
MY_API void my_msort(
    void *data[2], size_t nmemb, size_t size, my_comparator_t cmp);

MY_API_END

#endif
