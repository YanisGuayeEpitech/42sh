/*
** EPITECH PROJECT, 2020
** LibMy - misc module
** File description:
** The main header for the misc module
*/

/// @file
///
/// Miscellaneous utlities.
///
/// @since 0.1.0

#ifndef __LIBMY_MISC_H__
#define __LIBMY_MISC_H__

#include "libmy/internal/attributes.h"

MY_API_BEGIN

#ifndef LIBMY_MODULE_MISC
#error "LibMy: 'libmy/misc.h' is included, \
but misc module is not present"
#endif

/// Computes the length of a NULL-terminated pointer array.
///
/// @param array The array.
///
/// @returns The length of the array, or 0 if @c array is @c NULL.
/// @since 0.1.0
MY_API int my_ptr_array_len(void const *array[]);

/// Sorts a int array in ascending order?
///
/// @param tab  The array.
/// @param size The number of elements in @c tab.
///
/// @since 0.1.0
MY_API void my_sort_int_array(int *tab, int size);

/// Swaps two ints.
///
/// @param a Will contain the contents of @c b.
/// @param b Will contain the contents of @c a.
///
/// @since 0.1.0
MY_API void my_swap(int *a, int *b);

MY_API_END

#endif
