/*
** EPITECH PROJECT, 2020
** LibMy - config
** File description:
** Detects the endianess of this computer
*/

#include "libmy_config.h"

static int is_big_endian(char *data)
{
    for (char i = 0; i < sizeof(int); ++i) {
        if (*data != i)
            return 0;
        ++data;
    }
    return 1;
}

static int is_little_endian(char *data)
{
    for (char i = sizeof(int) - 1; i > 0; --i) {
        if (*data != i)
            return 0;
        ++data;
    }
    return *data == 0;
}

endian_t get_endian(void)
{
    endian_test_t test;

    test.value = 0;
    for (char i = 0; i < sizeof(int); ++i) {
        test.value <<= 8;
        test.value |= i;
    }
    (void)PROPERTIES_NAMES;
    (void)PROPERTIES_VALUES;
    if (is_big_endian(test.data))
        return CONFIG_BIG_ENDIAN;
    if (is_little_endian(test.data))
        return CONFIG_LITTLE_ENDIAN;
    return CONFIG_INVALID_ENDIAN;
}
