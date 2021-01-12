/*
** EPITECH PROJECT, 2020
** LibMy - ascii module
** File description:
** The main header for the ascii module
*/

#ifndef __LIBMY_ASCII_H_
#define __LIBMY_ASCII_H_

#include "libmy/internal/attributes.h"

MY_API_BEGIN

#ifndef LIBMY_MODULE_ASCII
#error "LibMy: 'libmy/ascii.h' is included, \
but ascii module is not present"
#endif

#include <stddef.h>

MY_API char *my_revstr(char *str);
MY_API char *my_strcapitalize(char *str);
MY_API char *my_strcat(char *dest, char const *src);
MY_API char *my_strchr(const char *str, char c);
MY_API int my_strcmp(char const *s1, char const *s2);
MY_API char *my_strcpy(char *dst, char const *src);
MY_API int my_stricmp(char const *s1, char const *s2);
MY_API int my_strincmp(char const *s1, char const *s2, int n);
MY_API int my_str_isalpha(char const *str);
MY_API int my_str_islower(char const *str);
MY_API int my_str_isnum(char const *str);
MY_API int my_str_isprintable(char const *str);
MY_API int my_str_isupper(char const *str);
MY_API size_t my_strlen(char const *str);
MY_API char *my_strlowcase(char *str);
MY_API char *my_strncat(char *dest, char const *src, int nb);
MY_API int my_strncmp(char const *s1, char const *s2, int n);
MY_API char *my_strncpy(char *dst, char const *src, int n);
MY_API char *my_strstr(char const *str, char const *to_find);
MY_API char *my_strstr_n(char const *str, int str_len,
char const *to_find, int to_find_len);
MY_API char *my_strupcase(char *str);

#ifdef LIBMY_ALLOW_MALLOC
MY_API void my_free_str_array(char *array[], int len);
MY_API char *my_strdup(char const *src);
MY_API char **my_str_to_word_array(char const *str);
#endif

MY_INLINE int my_isalpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

MY_INLINE int my_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

MY_INLINE int my_isalnum(char c)
{
    return my_isalpha(c) || my_isdigit(c);
}

MY_INLINE int my_isblank(char c)
{
    return c == ' ' || c == '\t';
}

MY_INLINE int my_iscntrl(char c)
{
    return (c >= 0x00 && c <= 0x1F) || c == 0x7F;
}

MY_INLINE int my_isgraph(char c)
{
    return c > ' ' && c <= '~';
}

MY_INLINE int my_islower(char c)
{
    return c >= 'a' && c <= 'z';
}

MY_INLINE int my_isprint(char c)
{
    return c >= ' ' && c <= '~';
}

MY_INLINE int my_ispunct(char c)
{
    return my_isgraph(c) && !my_isalnum(c);
}

MY_INLINE int my_isspace(char c)
{
    return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
    c == '\v';
}

MY_INLINE int my_isupper(char c)
{
    return c >= 'A' && c <= 'Z';
}

MY_INLINE int my_isxdigit(char c)
{
    return my_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

MY_INLINE char my_toupper(char c)
{
    if (my_islower(c))
        return c & 0xdf;
    return c;
}

MY_INLINE char my_tolower(char c)
{
    if (my_isupper(c))
        return c | 0x20;
    return c;
}

MY_API_END

#endif
