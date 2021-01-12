/*
** EPITECH PROJECT, 2020
** LibMy - misc module
** File description:
** sorts the passed int array
*/

#include "libmy/misc.h"

static void my_sort_int_array_swap(int *array, int i)
{
    if (array[i] > array [i + 1]) {
        my_swap(array + i, array + i + 1);
    }
}

MY_API void my_sort_int_array(int *array, int size)
{
    if (!array)
        return;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j + 1 < size - i; ++j) {
            my_sort_int_array_swap(array, j);
        }
    }
}
