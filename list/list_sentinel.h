#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    struct node_s *prev;
    struct node_s *next;
    void *data;
} node_s_t, list_s_t;