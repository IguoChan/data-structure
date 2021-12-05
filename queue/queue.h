#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "list/doubly_linked_list.h"

typedef struct queue {
    struct node *head;
    struct node *tail;
    int cnt;
} queue_t;

#define queue_create()          (queue_t *)list_create()
#define enqueue(que, data)      list_append((list_t*)(que), (data))
#define dequeue(que)            list_retrieve_data((list_t*)(que), (que) ? (que)->head : NULL)
#define queue_destory(que)      list_destory((list_t*)que)

#endif