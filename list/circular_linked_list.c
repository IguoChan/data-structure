#include "circular_linked_list.h"
#ifndef CHOOSE_DOUBLY_LINK_LIST

typedef struct node
{
    struct node *prev;
    struct node *next;
    void *data;
    unsigned int cnt;
} node_t;

list_t *list_create()
{
    // nil是哨兵节点
    list_t *nil;
    nil = malloc(sizeof(list_t));
    if (!nil) return NULL;

    nil->prev = nil->next = nil;
    nil->cnt = 0;
    return nil;
}

int list_append(list_t *list, void *data)
{
    node_t *node;

    if (!list || !data)
        return -1;

    node = malloc(sizeof(node_t));
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

int list_prepend(list_t *list, void *data)
{
    node_t *node;

    if (!list || !data)
        return -1;

    node = malloc(sizeof(node_t));
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

int list_insert_at(list_t *list, unsigned int pos, void *data)
{
    int i;
    node_t *f_node;
    node_t *i_node;

    if (!list || !data || pos > list->cnt) return -1;

    f_node = list->next;
    for (i = 0; i < pos && f_node != list; i++)
        f_node = f_node->next;

    i_node = malloc(sizeof(node_t));
    if (!i_node) return -1;
    i_node->data = data;

    i_node->prev = f_node->prev;
    i_node->next = f_node;
    f_node->prev->next = i_node;
    f_node->prev = i_node;
    list->cnt++;

    return 0;
}

int list_insert_before(list_t *list, node_t *node, void *data)
{
    node_t *i_node;

    if (!list || !node || !data)
        return -1;

    i_node = malloc(sizeof(node_t));
    if (!i_node) return -1;
    i_node->data = data;

    i_node->prev = node->prev;
    i_node->next = node;
    node->prev->next = i_node;
    node->prev = i_node;
    list->cnt++;

    return 0;
}

int list_insert_after(list_t *list, node_t *node, void *data)
{
    node_t *i_node;

    if (!list || !node || !data)
        return -1;
    
    i_node = malloc(sizeof(node_t));
    if (!i_node) return -1;
    i_node->data = data;

    i_node->prev = node;
    i_node->next = node->next;
    node->next->prev = i_node;
    node->next = i_node;
    list->cnt--;

    return 0;
}

void *list_retrieve_data(list_t *list, node_t *node)
{
    void *data;

    if (!list || !node || node == list)
        return NULL;

    node->prev->next = node->next;
    node->next->prev = node->prev;
    list->cnt--;
    data = node->data;
    free(node);
    return data;
}

void *list_retrieve_data_at(list_t *list, unsigned int pos)
{
    int i;
    node_t *node;

    if (!list) return NULL;

    node = list->next;
    for (i = 0; i < pos && node != list; i++)
        node = node->next;

    return list_retrieve_data(list, node);
}

int list_remove_data(list_t *list, void *data)
{
    node_t *node;

    if (!list || !data) return -1;

    for (node = list->next; node != list && data != node->data; node = node->next); //注意这个分号，一定要加


    return list_retrieve_data(list, node) ? 0 : -1;
}

void list_print(list_t *list)
{
    node_t *node;
    int i = 0;
    printf("[CNT:%d]: {NIL} ——> ", list->cnt);
    for (node = list->next; node != list; node = node->next, i++)
        printf("{Node[%d]: %d} ——> ", i, *(int*)(node->data));
    printf("{NIL}\n");
}
#endif