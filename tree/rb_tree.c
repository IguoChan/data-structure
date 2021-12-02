#include "rb_tree.h"

rbTreeNode_t *NilNode = NULL;

void refreshe_nilnode()
{
    NilNode->parent = NilNode->left = NilNode->right = NilNode;
    NilNode->color = BLACK;
    NilNode->data = INT_MAX;
}

rbTree_t *rbtree_init()
{
    rbTree_t *T;

    if (!NilNode) {
        NilNode = malloc(sizeof(rbTreeNode_t));
        if (!NilNode) return NULL;
        NilNode->parent = NilNode->left = NilNode->right = NilNode;
        NilNode->color = BLACK;
        NilNode->data = INT_MAX;
    }

    T = malloc(sizeof(rbTree_t));
    if (!T) return NULL;
    T->root = NilNode;

    return T;
}

rbTreePos_t *rbtree_search1(rbTreeNode_t *node, myElement x)
{
    if (node == NilNode) return NULL;

    if (x == node->data) return node;

    if (x < node->data) return rbtree_search1(node->left, x);
    else return rbtree_search1(node->right, x);
}

rbTreePos_t *rbtree_search(rbTree_t *T, myElement x)
{
    if (T == NULL) return NULL;

    return rbtree_search1(T->root, x);
}

rbTreePos_t *rbtree_min1(rbTreeNode_t *node)
{
    if (node == NilNode) return NULL;

    rbTreePos_t *min = node;
    while (min->left != NilNode)
    {
        min = min->left;
    }
    return min;
}

rbTreePos_t *rbtree_min(rbTree_t *T)
{
    if (T == NULL) return NULL;

    return rbtree_min1(T->root);
}

rbTreePos_t *rbtree_max1(rbTreeNode_t *node)
{
    if (node == NilNode) return NULL;

    rbTreePos_t *min = node;
    while (min->right != NilNode)
    {
        min = min->right;
    }
    return min;
}

rbTreePos_t *rbtree_max(rbTree_t *T)
{
    if (T == NULL) return NULL;

    return rbtree_max1(T->root);
}

void rbtree_left_rotate(rbTree_t *T, rbTreeNode_t *x)
{
    rbTreeNode_t *y = x->right;

    // y的左子树移植为x的右子树
    x->right = y->left;
    if (y->left != NilNode) y->left->parent = x;

    // x的父节点移植为y的父节点
    y->parent = x->parent;
    if (x->parent == NilNode) T->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    // x移植为y的左子树
    y->left = x;
    x->parent = y;
}

void rbtree_right_rotate(rbTree_t *T, rbTreeNode_t *y)
{
    rbTreeNode_t *x = y->left;

    // x的右子树移植为y的左子树
    y->left = x->right;
    if (x->right != NilNode) x->right->parent = y;

    // y的父节点一直为x的父节点
    x->parent = y->parent;
    if (y->parent == NilNode) T->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    // y移植为x的右子树
    x->right = y;
    y->parent = x;
}

void rbtree_insert_fixup(rbTree_t *T, rbTreeNode_t *node)
{
    rbTreeNode_t *uncle;

    // 如果其父节点是红色的，那么就不满足性质4，我们需要对其进行重新涂色
    // 如果parent是红色的，那么其一定有parent->parent
    while (node->parent->color == RED) {
        // 如果其父节点是其祖父节点的左儿子
        if (node->parent == node->parent->parent->left) {
            uncle = node->parent->parent->right;
            // 如果其叔节点是红色
            if (uncle->color == RED) {
                // case1
                node->parent->color = BLACK;// 将其父节点涂黑
                uncle->color = BLACK;       // 将其叔节点涂黑
                node->parent->parent->color = RED; // 将其祖父节点涂红
                node = node->parent->parent;// 利用其祖父节点作为循环量继续循环
            } else if (node == node->parent->right) {
                // case2
                node = node->parent;
                rbtree_left_rotate(T, node);
            } else {
                // case3
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rbtree_right_rotate(T, node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->left;
            // 如果其叔节点是红色
            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else if (node == node->parent->left) {
                node = node->parent;
                rbtree_right_rotate(T, node);
            } else {
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rbtree_left_rotate(T, node->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void rbtree_insert(rbTree_t *T, myElement x)
{
    if (T == NULL) return;

    rbTreeNode_t *X = T->root;
    rbTreeNode_t *Y = NilNode;

    while (X != NilNode) {
        Y = X;
        if (x < X->data) X = X->left;
        else X = X->right;
    }


    rbTreeNode_t *Z = malloc(sizeof(rbTreeNode_t));
    if (!Z) return;
    Z->data = x;
    Z->parent = Y;
    Z->left = Z->right = NilNode;
    Z->color = RED;

    if (Y == NilNode) T->root = Z;
    else if (x < Y->data) Y->left = Z;
    else Y->right = Z;

    rbtree_insert_fixup(T, Z);
}

int rbtree_height(rbTreeNode_t *node)
{
    if (node == NilNode) return 0;

    return MAX_INT(rbtree_height(node->left), rbtree_height(node->right)) + 1;
}

void rbtree_transplant(rbTree_t *T, rbTreeNode_t *u, rbTreeNode_t *v)
{
    if (u->parent == NilNode) T->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void rbtree_delete_fixup(rbTree_t *T, rbTreeNode_t *node)
{
    rbTreeNode_t *w;
    while(node != T->root && node->color == BLACK) {
        if (node == node->parent->left) {
            w = node->parent->right;
            if (w->color == RED) {
                // case1
                w->color = BLACK;
                node->parent->color = RED;
                rbtree_left_rotate(T, node->parent);
                w = node->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // case2
                w->color = RED;
                node = node->parent;
            } else if (w->right->color == BLACK) {
                // case3
                w->left->color = BLACK;
                w->color = RED;
                rbtree_right_rotate(T, w);
                w = node->parent->right;
            } else {
                // case4
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->right->color = BLACK;
                rbtree_left_rotate(T, node->parent);
                node = T->root;
            }
        } else if (node == node->parent->right) {
            // 镜像
            w = node->parent->left;
            if (w->color == RED) {
                // case1
                w->color = BLACK;
                node->parent->color = RED;
                rbtree_right_rotate(T, node->parent);
                w = node->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // case2
                w->color = RED;
                node = node->parent;
            } else if (w->left->color == BLACK) {
                // case3
                w->right->color = BLACK;
                w->color = RED;
                rbtree_left_rotate(T, w);
                w = node->parent->left;
            } else {
                // case4
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(T, node->parent);
                node = T->root;
            }
        }
    }
    node->color = BLACK;
}

void rbtree_delete1(rbTree_t *T, rbTreeNode_t *node, myElement x)
{
    if (node == NilNode) return;

    rbTreeNode_t *origin;
    rbTreeNode_t *tmp;

    if (x < node->data) return rbtree_delete1(T, node->left, x);
    else if (x > node->data) return rbtree_delete1(T, node->right, x);
    // 以下两种情况都是 x == node->data
    else if (node->left != NilNode && node->right != NilNode) {
        // 两个儿子
        tmp = rbtree_min1(node->right);
        node->data = tmp->data;
        return rbtree_delete1(T, node->right, tmp->data);
    } else {
        tmp = node;
        // 如果没有左儿子，则将右儿子代替node，不管右儿子是不是NilNode
        if (node->left == NilNode) {
            origin = node->right;
            rbtree_transplant(T, node, node->right);
        }
        else if (node->right == NilNode) {
            origin = node->left;
            rbtree_transplant(T, node, node->left);
        }
    }

    if (tmp->color == BLACK) {
        rbtree_delete_fixup(T, origin);
    }
    free(tmp);
}

void rbtree_delete(rbTree_t *T, myElement x)
{
    if (T == NULL) return;

    return rbtree_delete1(T, T->root, x);
}

void rbtree_printLevel(rbTreeNode_t *node, int level)
{
    if (node == NilNode) {
        if (level == 1) printf("NULL  ");
        else {
            rbtree_printLevel(node->left, level - 1);
            rbtree_printLevel(node->right, level - 1);
        }

    } else {
        if (level == 1) {
            printf("%d", node->data);
            if (node->color == RED) printf("[R]  ");
            else printf("[B]  ");
        } else {
            rbtree_printLevel(node->left, level - 1);
            rbtree_printLevel(node->right, level - 1);
        }
    }
}

void rbtree_BSF_print(rbTree_t *T)
{
    if (T == NULL) return;

    rbTreeNode_t *root  = T->root;
    int height = rbtree_height(root);
    for (int i = 1; i <= height; i++) {
        rbtree_printLevel(root, i);
        printf("\n");
    }
}
