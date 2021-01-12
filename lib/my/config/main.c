/*
** EPITECH PROJECT, 2020
** LibMy - config
** File description:
** The main for libmy-config
*/

#include <unistd.h>
#include <stddef.h>
#include "libmy_config.h"

static void print_property(int fd, char const *property)
{
    size_t len = 0;

    while (property[len])
        ++len;
    write(fd, property, len);
}

static void print_usage(int fd, char const *program_name)
{
    size_t properties = sizeof(PROPERTIES_NAMES) / sizeof(*PROPERTIES_NAMES);

    write(fd, "usage: ", 7);
    print_property(fd, program_name);
    write(fd, " <PROPERTY>\n", 12);
    if (properties == 0) {
        write(fd, "No available properties\n", 24);
        return;
    }
    write(fd, "Available properties:\n", 22);
    for (size_t i = 0; i < properties; ++i) {
        write(fd, " - ", 3);
        print_property(fd, PROPERTIES_NAMES[i]);
        write(fd, "\n", 1);
    }
}

int main(int argc, char *argv[])
{
    char const *property;

    if (argc != 2) {
        print_usage(2, argv[0]);
        return -1;
    }
    property = get_property(argv[1]);
    if (!property) {
        write(2, "cannot find property \"", 22);
        print_property(2, argv[1]);
        write(2, "\"\n", 2);
        return -2;
    }
    print_property(1, property);
    write(1, "\n", 1);
    (void)PROPERTIES_VALUES;
    return 0;
}
