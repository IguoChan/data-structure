#include "tree.h"

typedef struct rbTree rbTree_t;
typedef struct rbTreeNode rbTreePos_t;

rbTree_t *rbtree_init();
void rbtree_insert(rbTree_t *T, myElement x);
void rbtree_BSF_print(rbTree_t *T);