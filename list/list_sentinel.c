#include "list_sentinel.h"

list_s_t *list_s_creat()
{
    // nil是哨兵节点
    list_s_t *nil;
    nil = malloc(sizeof(list_s_t));
    if (!nil) return NULL;

    nil->prev = nil->next = nil;
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
    return 0;
}

void list_s_print(list_s_t *list)
{
    node_s_t *node;
    int i = 0;
    printf("Header-->");
    for (node = list->next; node != list; node = node->next, i++)
        printf("Node[%d]: %d-->", i, *(int*)(node->data));
    printf("NULL\n");
}