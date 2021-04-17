/*
** EPITECH PROJECT, 2020
** LibMy - io module internals
** File description:
** Internals for the IO streams.
*/

#ifndef __LIBMY_INTERNAL_IOSTREAM_H__
#define __LIBMY_INTERNAL_IOSTREAM_H__

#include "libmy/internal/attributes.h"

MY_API_BEGIN

#include <stddef.h>

typedef size_t (*p_my_fread_impl_t)(void *, void *, size_t, size_t);
typedef size_t (*p_my_fwrite_impl_t)(void *, const void *, size_t, size_t);
typedef int (*p_my_fflush_impl_t)(void *);
typedef void (*p_my_ffree_impl_t)(void *);
typedef int (*p_my_feof_impl_t)(void const *);
typedef int (*p_my_fset_threshold_impl_t)(void *, float);
typedef int (*p_my_fset_buf_impl_t)(void *, void *, size_t, void (*)(void *));
typedef void *(*p_my_fget_buf_impl_t)(const void *, size_t *);
typedef int (*p_my_fclose_impl_t)(void *);

typedef struct {
    p_my_fread_impl_t read;
    p_my_fwrite_impl_t write;
    p_my_fflush_impl_t flush;
    p_my_ffree_impl_t destroy;
    p_my_feof_impl_t eof;
    p_my_fset_threshold_impl_t set_threshold;
    p_my_fset_buf_impl_t set_buffer;
    p_my_fget_buf_impl_t get_buffer;
    p_my_fclose_impl_t close;
} p_my_iostream_vtable_t;

typedef struct {
    p_my_iostream_vtable_t const *vtable;
    int fd;
    int is_eof;
    float threshold;
    unsigned char *buf;
    size_t buf_cap;
    size_t buf_len;
    void (*free_buf)(void *);
} p_my_iostream_unix_t;

typedef struct {
    p_my_iostream_vtable_t const *vtable;
    unsigned char *buf;
    size_t count;
    size_t limit;
} p_my_iostream_memory_t;

typedef union {
    p_my_iostream_vtable_t const *vtable;
    p_my_iostream_unix_t unix_stream;
    p_my_iostream_memory_t memory_stream;
} p_my_iostream_t;

#if LIBMY_ALLOW_READ
MY_LOCAL size_t p_my_fread_unix(
    p_my_iostream_unix_t *input, void *ptr, size_t size, size_t nmemb);
    #define P_MY_FREAD_UNIX ((p_my_fread_impl_t)&p_my_fread_unix)
#else
    #define P_MY_FREAD_UNIX ((p_my_fread_impl_t)NULL)
#endif

MY_LOCAL size_t p_my_fread_memory(
    p_my_iostream_memory_t *input, void *ptr, size_t size, size_t nmemb);
MY_LOCAL size_t p_my_fread_void(
    void *input, void *ptr, size_t size, size_t nmemb);

MY_LOCAL size_t p_my_fwrite_unix(
    p_my_iostream_unix_t *output, const void *ptr, size_t size, size_t nmemb);
MY_LOCAL size_t p_my_fwrite_memory(p_my_iostream_memory_t *output,
    const void *ptr, size_t size, size_t nmemb);
MY_LOCAL size_t p_my_fwrite_void(
    void *output, const void *ptr, size_t size, size_t nmemb);

MY_LOCAL int p_my_fflush_unix(p_my_iostream_unix_t *stream);

MY_LOCAL void p_my_ffree_unix(p_my_iostream_unix_t *stream);

MY_LOCAL int p_my_feof_unix(p_my_iostream_unix_t const *stream);
MY_LOCAL int p_my_feof_memory(p_my_iostream_memory_t const *stream);
MY_LOCAL int p_my_feof_void(void const *stream);

MY_LOCAL int p_my_fset_threshold_unix(
    p_my_iostream_unix_t *stream, float threshold);

MY_LOCAL int p_my_fset_buffer_unix(p_my_iostream_unix_t *stream, void *buf,
    size_t buf_cap, void (*free_buf)(void *));

MY_LOCAL void *p_my_fget_buffer_unix(
    p_my_iostream_unix_t const *stream, size_t *size);
MY_LOCAL void *p_my_fget_buffer_memory(
    p_my_iostream_memory_t const *stream, size_t *size);

#if LIBMY_ALLOW_CLOSE
MY_LOCAL int p_my_fclose_unix(p_my_iostream_unix_t *stream);
    #define P_MY_FCLOSE_UNIX ((p_my_fclose_impl_t)&p_my_fclose_unix)
#else
    #define P_MY_FCLOSE_UNIX ((p_my_fclose_impl_t)NULL)
#endif

MY_API_END

#endif
