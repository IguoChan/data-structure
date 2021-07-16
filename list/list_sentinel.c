#include "list_sentinel.h"

list_s_t *list_s_create()
{
    // nil是哨兵节点
    list_s_t *nil;
    nil = malloc(sizeof(list_s_t));
    if (!nil) return NULL;

    nil->prev = nil->next = nil;
    nil->cnt = 0;
    return nil;
}

int list_s_append(list_s_t *list, void *data)
{
    node_s_t *node;

    if (!list || !data)
        return -1;

    node = malloc(sizeof(node_s_t));
    if (!node)
        return -1;
    node->data = data;

    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
    list->cnt++;
    return 0;
}

int list_s_prepend(list_s_t *list, void *data)
{
    node_s_t *node;

    if (!list || !data)
        return -1;

    node = malloc(sizeof(node_s_t));
    if (!node)
        return -1;
    node->data = data;

    node->prev = list;
    node->next = list->next;
    list->next->prev = node;
    list->next = node;
    list->cnt++;
    return 0;
}

int list_s_insert_at(list_s_t *list, unsigned int pos, void *data)
{
    int i;
    node_s_t *f_node;
    node_s_t *i_node;

    if (!list || !data || pos > list->cnt) return -1;

    f_node = list->next;
    for (i = 0; i < pos && f_node != list; i++)
        f_node = f_node->next;

    i_node = malloc(sizeof(node_s_t));
    if (!i_node) return -1;
    i_node->data = data;

    i_node->prev = f_node->prev;
    i_node->next = f_node;
    f_node->prev->next = i_node;
    f_node->prev = i_node;
    list->cnt++;

    return 0;
}

int list_s_insert_before(list_s_t *list, node_s_t *node, void *data)
{
    node_s_t *i_node;

    i_node = malloc(sizeof(node_s_t));
    if (!i_node) return -1;
    i_node->data = data;

    i_node->prev = node->prev;
    i_node->next = node;
    node->prev->next = i_node;
    node->prev = i_node;
    list->cnt++;

    return 0;
}

void *list_s_retrieve_data(list_s_t)

void list_s_print(list_s_t *list)
{
    node_s_t *node;
    int i = 0;
    printf("[CNT:%d]: {NIL}——> ", list->cnt);
    for (node = list->next; node != list; node = node->next, i++)
        printf("{Node[%d]: %d} ——> ", i, *(int*)(node->data));
    printf("{NIL}\n");
}