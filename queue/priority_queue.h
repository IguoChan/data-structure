#ifndef _P_QUEUE_H
#define _P_QUEUE_H

#include <stdio.h>
#include <limits.h>

#define MIN_PQ_SIZE 128
#define MIN_DATA INT_MIN

typedef int MyElement;

typedef struct heap pQueue_t;

typedef struct heap {
    int cap;
    int size;
    MyElement *elems;
} heap_t;

pQueue_t *pQueue_initialize(int maxElems);
int pQueue_insert(pQueue_t *H, MyElement x);
MyElement pQueue_get_and_delete_min(pQueue_t *H);
void pQueue_print(pQueue_t *H);

#endif