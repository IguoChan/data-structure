#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *prev;
    struct node *next;
    void *data;
} node_t;

typedef struct list
{    
    struct node *head;
    struct node *tail;
    unsigned int cnt;
} list_t;

typedef int (*match_t)(void *, void *);

#define list_for_each_entry(pos, list, node)                                                    \
    for (node = (NULL != (void*)list) ? (list)->head : NULL, pos = (node ? node->data : NULL);  \
        pos;                                                                                    \
        node = node->next, pos = node ? node->data : NULL)

#define list_for_each_entry_safe(pos, list, node, nex)                                          \
    for (node = (NULL != (void*)list) ? (list)->head : NULL, pos = (node ? node->data : NULL),  \
    	nex = (node ? node->next : NULL);                                                       \
        pos;                                                                                    \
        node = nex, pos = node ? node->data : NULL, nex = (node ? node->next : NULL))


list_t *list_create(void);
int list_append(list_t *list, void *data);
void list_print(list_t *list);
int list_prepend(list_t *list, void *data);
int list_insert_at(list_t *list, unsigned int pos, void *data);