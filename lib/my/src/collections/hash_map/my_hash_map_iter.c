/*
** EPITECH PROJECT, 2021
** LibMy - collections module
** File description:
** Hash map iteration
*/

#include "libmy/collections/hash_map.h"

MY_COLLECTIONS_API void my_hash_map_iter_init(
    my_hash_map_iter_t *iter, my_hash_map_t const *map)
{
    *iter = (my_hash_map_iter_t){.map = map};

    while (iter->bucket_index < map->capacity) {
        iter->next_item = map->buckets[iter->bucket_index];
        if (iter->next_item != NULL)
            break;
        ++(iter->bucket_index);
    }
}

MY_COLLECTIONS_API int my_hash_map_iter_has_next(
    my_hash_map_iter_t const *iter)
{
    return iter->next_item != NULL;
}

MY_COLLECTIONS_API int my_hash_map_iter_next(my_hash_map_iter_t *iter)
{
    size_t cap = iter->map->capacity;
    p_my_hash_map_item_t **buckets = iter->map->buckets;

    if (iter->next_item == NULL)
        return 0;
    iter->key = P_MY_HM_KEY(iter->map, iter->next_item);
    iter->value = P_MY_HM_VAL(iter->map, iter->next_item);
    if (iter->next_item->next != NULL) {
        iter->next_item = iter->next_item->next;
        return 1;
    }
    iter->next_item = NULL;
    while (iter->next_item == NULL && ++iter->bucket_index < cap)
        iter->next_item = buckets[iter->bucket_index];
    return 1;
}
