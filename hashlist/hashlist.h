#include "uthash.h"

typedef struct hashlist_int hashlist_int_t;

hashlist_int_t *hashlist_create_int();
int hashlist_add_int(hashlist_int_t *hl, int key, void *data);
void *hashlist_find_int(hashlist_int_t *hl, int key);
int hashlist_delete_int(hashlist_int_t *hl, int key);
int hashlist_destroy_int(hashlist_int_t *hl);