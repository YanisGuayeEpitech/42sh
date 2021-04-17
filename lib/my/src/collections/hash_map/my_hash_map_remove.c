/*
** EPITECH PROJECT, 2021
** LibMy - collections module
** File description:
** Removes an item from the hash map
*/

#include <assert.h>

#include "libmy/memory/alloc.h"
#include "libmy/collections/hash_map.h"

static void my_hash_map_drop_kv(my_hash_map_t *map, p_my_hash_map_item_t *item)
{
    if (map->key_drop)
        (*map->key_drop)(P_MY_HM_KEY(map, item));
    if (map->value_drop)
        (*map->value_drop)(P_MY_HM_VAL(map, item));
}

MY_COLLECTIONS_API int my_hash_map_remove(my_hash_map_t *map, void const *key)
{
    p_my_hash_map_item_t **item;

    assert(map != NULL);
    assert(key != NULL);
    if (map->buckets == NULL)
        return 0;
    item = &map->buckets[my_hash_map_hash_key(map, key) % map->capacity];
    while (*item != NULL && (*map->compare)(key, P_MY_HM_KEY(map, *item)))
        item = &(*item)->next;
    if (*item == NULL)
        return 0;
    my_hash_map_drop_kv(map, *item);
    my_sfree((void **)item);
    --(map->length);
    return 1;
}
