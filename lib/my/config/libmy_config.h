/*
** EPITECH PROJECT, 2020
** LibMy - config
** File description:
** The header file for libmy-config
*/

#ifndef __LIBMY_CONFIG_H__
#define __LIBMY_CONFIG_H__

// The (sorted) array of properties keys
static const char *PROPERTIES_NAMES[] = {
    "defines",
    "flags",
    "include_path",
    "library_path",
    "modules",
    "version",
    "version_major",
    "version_minor",
    "version_patch"
};

// The array of properties names, sorted by keys
static const char *PROPERTIES_VALUES[] = {
    "<defines placeholder>",
    CONFIG_FLAGS,
    CONFIG_INCLUDE_PATH,
    CONFIG_LIBRARY_PATH,
    CONFIG_MODULES,
    CONFIG_VERSION_MAJOR "." CONFIG_VERSION_MINOR "." CONFIG_VERSION_PATCH,
    CONFIG_VERSION_MAJOR,
    CONFIG_VERSION_MINOR,
    CONFIG_VERSION_PATCH
};

#define DEFINES_BIG_ENDIAN CONFIG_DEFINES " LIBMY_BIG_ENDIAN"
#define DEFINES_LITTLE_ENDIAN CONFIG_DEFINES " LIBMY_LITTLE_ENDIAN"
#define DEFINES_POS (0)

typedef union {
    int value;
    char data[sizeof(int)];
} endian_test_t;

typedef enum {
    CONFIG_BIG_ENDIAN,
    CONFIG_LITTLE_ENDIAN,
    CONFIG_INVALID_ENDIAN
} endian_t;

char const *get_property(char const *key);
endian_t get_endian(void);

#endif
