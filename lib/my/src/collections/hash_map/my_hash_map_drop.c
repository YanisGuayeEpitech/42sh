/*
** EPITECH PROJECT, 2021
** LibMy - collections module
** File description:
** Removes an item from the hash map
*/

#include <assert.h>
#include <stdlib.h>

#include "libmy/collections/hash_map.h"

static void my_hash_map_remove_bucket(
    my_hash_map_t *map, p_my_hash_map_item_t **bucket)
{
    p_my_hash_map_item_t *item;
    p_my_hash_map_item_t *next = *bucket;

    do {
        item = next;
        next = item->next;
        if (map->key_drop)
            (*map->key_drop)(P_MY_HM_KEY(map, item));
        if (map->value_drop)
            (*map->value_drop)(P_MY_HM_VAL(map, item));
        free(item);
    } while (next != NULL);
    *bucket = NULL;
}

MY_COLLECTIONS_API void my_hash_map_drop(my_hash_map_t *map)
{
    assert(map != NULL);
    if (map->buckets == NULL || map->capacity == 0)
        return;
    for (size_t i = 0; i < map->capacity; ++i) {
        p_my_hash_map_item_t **bucket = map->buckets + i;

        if (*bucket != NULL)
            my_hash_map_remove_bucket(map, bucket);
    }
    free(map->buckets);
    map->length = 0;
    map->capacity = 0;
}
