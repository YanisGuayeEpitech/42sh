/*
** EPITECH PROJECT, 2021
** LibMy - collections module
** File description:
** Checks if an element is in the map
*/

#include <assert.h>

#include "libmy/collections/hash_map.h"

MY_COLLECTIONS_API int my_hash_map_contains(
    my_hash_map_t *map, void const *key)
{
    p_my_hash_map_item_t *item;

    assert(map != NULL);
    assert(key != NULL);
    if (map->buckets == NULL)
        return 0;
    item = map->buckets[my_hash_map_hash_key(map, key) % map->capacity];
    while (item != NULL && (*map->compare)(key, P_MY_HM_KEY(map, item)))
        item = item->next;
    return item != NULL;
}
