/*
** EPITECH PROJECT, 2020
** LibMy - hash module internals
** File description:
** Core attribute definitions
*/

#ifndef __LIBMY_INTERNAL_HASH_H__
#define __LIBMY_INTERNAL_HASH_H__

#include <stddef.h>
#include "libmy/internal/attributes.h"
#include "libmy/internal/types.h"

typedef struct {
    my_u64_t key_1;
    my_u64_t key_2;
    /// The number of bytes processed.
    size_t length;
    /// Unprocessed bytes (Little Endian).
    my_u64_t tail;
    /// Number of valid bytes in @c tail
    size_t ntail;
    my_u64_t state_0;
    my_u64_t state_1;
    my_u64_t state_2;
    my_u64_t state_3;
} p_my_hasher_t;

/// Resets the state of a hasher.
MY_LOCAL void p_my_hasher_reset(p_my_hasher_t *hasher);

/// Loads up to 7 bytes from the given buffer in little endian.
///
/// @param length MUST be lower than 8.
MY_LOCAL my_u64_t p_my_hash_load_from_mem(
    unsigned char const *buf, size_t start, size_t length);

#define P_MY_UNWRAP_STATE(H) &H->state_0, &H->state_1, &H->state_2, &H->state_3

MY_LOCAL void p_my_siphash13_c_rounds(p_my_hasher_t *hasher);
MY_LOCAL void p_my_siphash13_d_rounds(p_my_hasher_t *hasher);

#endif // !defined(__LIBMY_INTERNAL_HASH_H__)
