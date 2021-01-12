/*
** EPITECH PROJECT, 2020
** LibMy unit tests
** File description:
** Tests the my_binary_search function
*/

#include <criterion/criterion.h>
#include <string.h>
#include "libmy/memory.h"

Test(my_binary_search, null_array)
{
    cr_assert_eq(my_binary_search(NULL, "yeet", 34, &strcmp), NULL);
}

Test(my_binary_search, zero_len)
{
    char *array[] = { "yeet", "bob", "foo" };

    cr_assert_eq(my_binary_search((void **)array, "yeet", 0, &strcmp), NULL);
}

Test(my_binary_search, null_cmp)
{
    char *array[] = { "yeet", "bob", "foo" };

    cr_assert_eq(my_binary_search((void **)array, "yeet", 3, NULL), NULL);
}

Test(my_binary_search, not_found_before_start)
{
    char *array[] = { "bob", "foo", "yeet" };

    cr_assert_eq(my_binary_search((void **)array, "abc", 3, &strcmp), NULL);
}

Test(my_binary_search, not_found_after_end)
{
    char *array[] = { "bob", "foo", "yeet" };

    cr_assert_eq(my_binary_search((void **)array, "zzz", 3, &strcmp), NULL);
}

Test(my_binary_search, one_elem)
{
    char *array[] = { "yeet" };

    cr_assert_eq(my_binary_search((void **)array, "yeet", 1, &strcmp),
    array);
}

Test(my_binary_search, three_elems_find_begin)
{
    char *array[] = { "bob", "foo", "yeet" };

    cr_assert_eq(my_binary_search((void **)array, "bob", 3, &strcmp),
    array);
}

Test(my_binary_search, three_elems_find_middle)
{
    char *array[] = { "bob", "foo", "yeet" };

    cr_assert_eq(my_binary_search((void **)array, "foo", 3, &strcmp),
    array + 1);
}

Test(my_binary_search, three_elems_find_end)
{
    char *array[] = { "bob", "foo", "yeet" };

    cr_assert_eq(my_binary_search((void **)array, "yeet", 3, &strcmp),
    array + 2);
}

Test(my_binary_search, six_elems_find_begin)
{
    char *array[] = { "abc", "bar", "bob", "foo", "yeet", "zebra" };

    cr_assert_eq(my_binary_search((void **)array, "abc", 6, &strcmp),
    array);
}

Test(my_binary_search, six_elems_find_middle)
{
    char *array[] = { "abc", "bar", "bob", "foo", "yeet", "zebra" };

    cr_assert_eq(my_binary_search((void **)array, "bob", 6, &strcmp),
    array + 2);
}

Test(my_binary_search, six_elems_find_end)
{
    char *array[] = { "abc", "bar", "bob", "foo", "yeet", "zebra" };

    cr_assert_eq(my_binary_search((void **)array, "zebra", 6, &strcmp),
    array + 5);
}
