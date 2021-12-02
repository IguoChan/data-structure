#include "tree.h"

typedef struct rbTree rbTree_t;
typedef struct rbTreeNode rbTreePos_t;
typedef enum ColorType {RED, BLACK} ColorType;

typedef struct rbTreeNode {
    myElement data;
    struct rbTreeNode *parent;
    struct rbTreeNode *left;
    struct rbTreeNode *right;
    ColorType color;
} rbTreeNode_t;

struct rbTree {
    rbTreeNode_t *root;
};

rbTree_t *rbtree_init();
void rbtree_insert(rbTree_t *T, myElement x);
void rbtree_BSF_print(rbTree_t *T);
rbTreePos_t *rbtree_search(rbTree_t *T, myElement x);
rbTreePos_t *rbtree_min(rbTree_t *T);
rbTreePos_t *rbtree_max(rbTree_t *T);
void rbtree_delete(rbTree_t *T, myElement x);