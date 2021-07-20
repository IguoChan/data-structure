#include <stdio.h>
#include <stdlib.h>

#ifndef CHOOSE_DOUBLY_LINK_LIST
typedef struct node list_t;

list_t *list_create();
int list_append(list_t *list, void *data);
void list_print(list_t *list);
int list_prepend(list_t *list, void *data);
int list_insert_at(list_t *list, unsigned int pos, void *data);
void *list_retrieve_data_at(list_t *list, unsigned int pos);
int list_remove_data(list_t *list, void *data);
#endif