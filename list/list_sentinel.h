#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    struct node_s *prev;
    struct node_s *next;
    void *data;
    unsigned int cnt;
} node_s_t, list_s_t;

list_s_t *list_s_create();
int list_s_append(list_s_t *list, void *data);
void list_s_print(list_s_t *list);
int list_s_prepend(list_s_t *list, void *data);
int list_s_insert_at(list_s_t *list, unsigned int pos, void *data);