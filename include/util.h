/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Utility functions
*/

#ifndef __SHELL_UTIL_H__
#define __SHELL_UTIL_H__

#include <stddef.h>

#define DEFAULT_PATH "/usr/bin:/bin"

/// Contatenates the given components, adding a '/' if necessary.
///
/// @param dir_len The length in bytes of @c dir_name
/// @param dir_name The directory part of the path
/// @param file_name The file part to add.
///
/// @returns The path, or NULL if allocation failed.
char *sh_create_file_path(
    size_t dir_len, char const *dir_name, char const *file_name);

/// Frees an entry of a string pointer array.
///
/// For use with @c my_vec_free.
///
/// @param ptr The pointer to free.
void sh_free_entry(void *ptr);

/// Closes the file descriptor at @c fd and sets the value to -1.
///
/// Does nothing if @c *fd is already -1.
///
/// @param fd A pointer to the file descriptor.
///
/// @returns The return value of close(2), or 0 if @c *fd was -1 before the
/// call.
int sh_sclose(int *fd);

/// Closes a pair of file descriptors by calling @ref sh_shclose twice
///
/// @param pipefd The file descriptors, can be @c NULL.
int sh_sclose_pipe(int pipefd[2]);

#endif // !defined(__SHELL_UTIL_H__)
