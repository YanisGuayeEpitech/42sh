/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** completion
*/

#ifndef COMPLETION_H_
#define COMPLETION_H_

#include <stdbool.h>
#include <stddef.h>
#include <glob.h>

int sh_get_completion_list(
    glob_t *globbuf, char *prefix, char *word, bool first);

#endif /* !COMPLETION_H_ */