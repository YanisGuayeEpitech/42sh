/*
** EPITECH PROJECT, 2020
** LibMy - config
** File description:
** Retrieves a property
*/

#include <stddef.h>
#include "libmy_config.h"

// Taken from ascii/my_strcmp
static int property_cmp(char const *s1, char const *s2)
{
    if (!s1 && s2)
        return -1;
    if (!s2 && s1)
        return 1;
    if (!s1 && !s2)
        return 0;
    while (*s1 && *s2 && *s1 == *s2) {
        ++s1;
        ++s2;
    }
    return (int)*s1 - (int)*s2;
}

// Taken from core/my_binary_search
static void *property_binary_search(void * const array[], void const *to_find,
size_t len, int (*cmp)())
{
    if (!array || !cmp)
        return NULL;
    while (len != 0) {
        size_t mid = len / 2;
        int comparison = (*cmp)(to_find, array[mid]);

        if (comparison == 0)
            return (void *)(array + mid);
        if (comparison < 0) {
            len = mid;
            continue;
        } else if (mid + 1 >= len) {
            return NULL;
        }
        array += mid + 1;
        len -= mid + 1;
    }
    return NULL;
}

char const *get_defines(void)
{
    switch (get_endian()) {
    case CONFIG_BIG_ENDIAN:
        return DEFINES_BIG_ENDIAN;
    case CONFIG_LITTLE_ENDIAN:
        return DEFINES_LITTLE_ENDIAN;
    default:
        return CONFIG_DEFINES;
    }
}

char const *get_property(char const *key)
{
    char *found;
    size_t index;

    if (!key)
        return NULL;
    found = (char *)property_binary_search((void **)PROPERTIES_NAMES, key,
    sizeof(PROPERTIES_NAMES) / sizeof(*PROPERTIES_NAMES), &property_cmp);
    if (!found)
        return NULL;
    index = (found - (char *)PROPERTIES_NAMES) / sizeof(char *);
    if (index == DEFINES_POS)
        return get_defines();
    return PROPERTIES_VALUES[index];
}
