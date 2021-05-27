/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** path_completion
*/

#include <libmy/ascii.h>
#include <libmy/memory.h>

#include "completion.h"

int sh_get_completion_list(
    glob_t *globbuf, char *prefix, char *word, bool first)
{
    int flags = GLOB_TILDE | GLOB_MARK;
    bool need_sep = (prefix && prefix[my_strlen(prefix) - 1] != '/' && word
        && word[0] != '/');
    size_t pattern_len = my_strlen(prefix) + my_strlen(word) + 2 + need_sep;
    char pattern[pattern_len];

    if (!prefix || !word)
        return GLOB_NOMATCH;
    my_memset(pattern, 0, pattern_len);
    my_strcpy(pattern, prefix);
    if (need_sep)
        my_strcat(pattern, "/");
    my_strcat(pattern, word);
    my_strcat(pattern, "*");
    if (!first)
        flags |= GLOB_APPEND;
    globbuf->gl_offs = 0;
    return glob(pattern, flags, NULL, globbuf);
}