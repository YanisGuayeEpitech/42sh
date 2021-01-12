/*
** EPITECH PROJECT, 2020
** LibMy
** File description:
** The main LibMy header
*/

/// @file
///
/// The main header file for LibMy.
/// It includes the headers for the following modules:
/// - core
/// - ascii
/// - collections
/// - io
/// - math
/// - memory
/// - misc
/// - parsing
///
/// @note
/// The header files for the above modules will be included only
/// if they are present.
/// Please use the <tt>LIBMY_MODULE_&lt;NAME&gt;</tt> to test their presence.

#ifndef __LIBMY_H__
#define __LIBMY_H__

#if defined(LIBMY_MODULE_CORE)
#include "libmy/core.h"
#endif

#if defined(LIBMY_MODULE_ASCII)
#include "libmy/ascii.h"
#endif

#if defined(LIBMY_MODULE_COLLECTIONS)
#include "libmy/collections.h"
#endif

#if defined(LIBMY_MODULE_IO) && defined(LIBMY_MODULE_ASCII)
#include "libmy/io.h"
#endif

#if defined(LIBMY_MODULE_MATH)
#include "libmy/math.h"
#endif

#if defined(LIBMY_MODULE_MEMORY)
#include "libmy/memory.h"
#endif

#if defined(LIBMY_MODULE_MISC)
#include "libmy/misc.h"
#endif

#if defined(LIBMY_MODULE_PARSING) && defined(LIBMY_MODULE_ASCII)
#include "libmy/parsing.h"
#endif

#endif
