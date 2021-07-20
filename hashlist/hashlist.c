#include <string.h>

#include "hashlist.h"

typedef struct hashlist_int_data
{
    int key;
    void *data;
    UT_hash_handle hh;
} hashlist_int_data_t;


struct hashlist_int {
    hashlist_int_data_t *head;
    int cnt;
};

hashlist_int_t *hashlist_create_int()
{
    hashlist_int_t *hl = malloc(sizeof(hashlist_int_t));
    if (!hl) return NULL;

    memset(hl, 0, sizeof(hashlist_int_t));
    return hl;
}

int hashlist_add_int(hashlist_int_t *hl, int key, void *data)
{
    if (!hl) return -1;

    hashlist_int_data_t *s = NULL;

    HASH_FIND_INT(hl->head, &key, s);
    if (s) return -1;

    s = (hashlist_int_data_t*)malloc(sizeof(hashlist_int_data_t));
    if (!s) return -1;
    s->key = key;
    s->data = data;
    HASH_ADD_INT(hl->head, key, s);
    return 0;
}

void *hashlist_find_int(hashlist_int_t *hl, int key)
{
    if (!hl) return NULL;

    hashlist_int_data_t *s;

    HASH_FIND_INT(hl->head, &key, s);
    if (!s) return NULL;

    return s->data;
}

int hashlist_delete_int(hashlist_int_t *hl, int key)
{
    if (!hl) return -1;

    hashlist_int_data_t *s;

    HASH_FIND_INT(hl->head, &key, s);
    if (!s) return -1;

    HASH_DEL(hl->head, s);
    free(s);
}

int hashlist_destroy_int(hashlist_int_t *hl)
{
    if (!hl) return -1;

    hashlist_int_data_t *s, *tmp;

    HASH_ITER(hh, hl->head, s, tmp) {
        HASH_DEL(hl->head, s);
        free(s);
    }
    free(hl);
    return 0;
}