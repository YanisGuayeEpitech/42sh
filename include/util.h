/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Utility functions
*/

#ifndef __SHELL_UTIL_H__
#define __SHELL_UTIL_H__

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

#endif // !defined(__SHELL_UTIL_H__)
