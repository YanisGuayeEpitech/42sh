/*
** EPITECH PROJECT, 2020
** LibMy - collections module
** File description:
** The main header for the collections module
*/

/// @file
///
/// The collections module.
///
/// @since 0.1.0

#ifndef __LIBMY_COLLECTIONS_H__
#define __LIBMY_COLLECTIONS_H__

#ifndef LIBMY_MODULE_COLLECTIONS
#error "LibMy: 'libmy/collections.h' is included, \
but collections module is not present"
#endif

#ifndef LIBMY_ALLOW_MALLOC
#error "LibMy: collections module requires the 'allow_malloc' flag"
#endif

#include "libmy/collections/vec.h"

#endif
