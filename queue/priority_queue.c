#include <stdlib.h>
#include <stdbool.h>

#include "priority_queue.h"

pQueue_t *pQueue_initialize(int maxElems)
{
    if (maxElems < MIN_PQ_SIZE) return NULL;

    pQueue_t *H = malloc(sizeof(pQueue_t));
    if (!H) return NULL;

    H->elems = malloc((maxElems + 1) * sizeof(MyElement));
    if (!H->elems) {
        free(H);
        return NULL;
    }

    H->cap = maxElems;
    H->size = 0;
    H->elems[0] = MIN_DATA;

    return H;
}

bool is_full(pQueue_t *H)
{
    if (!H) return false;

    if (H->size >= H->cap) return true;
    else return false;
}

bool is_empty(pQueue_t *H)
{
    if (!H) return true;

    if (H->size <= 0) return true;
    else return false;
}

int pQueue_insert(pQueue_t *H, MyElement x)
{
    int i;

    if (is_full(H)) return -1;

    for (i = ++H->size; H->elems[i/2] > x; i /= 2)
        H->elems[i] = H->elems[i/2];

    H->elems[i] = x;
    return 0;
}

MyElement pQueue_get_and_delete_min(pQueue_t *H)
{
    int i, child;
    MyElement minElem, lastElem;

    if (is_empty(H)) return MIN_DATA;

    minElem = H->elems[1];
    lastElem = H->elems[H->size--];

    for (i = 1; i * 2 <= H->size; i = child) {
        child = i * 2;
        if (child != H->size && H->elems[child+1] < H->elems[child])
            child++;

        if (lastElem > H->elems[child])
            H->elems[i] = H->elems[child];
        else
            break;
    }
    H->elems[i] = lastElem;
    return minElem;
}

void pQueue_print(pQueue_t *H)
{
    for (int i = 1; i <= H->size; i++) printf("%d ", H->elems[i]);
    printf("\n");
}
