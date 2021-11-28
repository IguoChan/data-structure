#include "binary_tree.h"

typedef struct searchTreeNode
{
    myElement data; // use int for data
    struct searchTreeNode *left;
    struct searchTreeNode *right;
} searchTreeNode_t;

searchTree_t *search_tree_insert(myElement x, searchTree_t *T)
{
    if (T == NULL) {
        T = malloc(sizeof(searchTree_t));
        if (!T) return NULL;
        T->data = x;
        T->left = T->right = NULL;
    } else if (x < T->data) {
        T->left = search_tree_insert(x, T->left);
    } else if (x > T->data) {
        T->right = search_tree_insert(x, T->right);
    } else {
        /* do nothing*/
    }

    return T;
}

void destroy_search_tree(searchTree_t *T)
{
    if (T == NULL) return;

    searchTreeNode_t *pl = T->left;
    searchTreeNode_t *pr = T->right;
    T->left = NULL;
    T->right = NULL;
    free(T);
    T = NULL;
    destroy_search_tree(pl);
    destroy_search_tree(pr);
}

searchTreePos_t *search_tree_search(searchTree_t *T, myElement k)
{
    if (T == NULL) return NULL;

    if (k == T->data) {
        return T;
    }

    if (k < T->data) {
        return search_tree_search(T->left, k);
    } else {
        return search_tree_search(T->right, k);
    }
}

searchTreePos_t *search_tree_min(searchTree_t *T)
{
    if (T == NULL) return NULL;

    searchTreePos_t *min = T;
    while (min->left)
    {
        min = min->left;
    }
    return min;
}

searchTreePos_t *search_tree_max(searchTree_t *T)
{
    if (T == NULL) return NULL;

    searchTreePos_t *max = T;
    while (max->right)
    {
        max = max->right;
    }
    return max;
}

searchTreePos_t *delete_get_min(searchTree_t **T)
{
    if (T == NULL || *T == NULL) return NULL;

    searchTreePos_t *min;
    if ((*T)->left == NULL) {
        min = *T;
        *T = (*T)->right;
        return min;
    }

    return delete_get_min(&(*T)->left);
}

// 或者用底下这个
searchTree_t* getMinAndDelete(searchTree_t* T, int *res) {
    if (T == NULL) return NULL;
    searchTree_t *min = T;
    if (T->left == NULL) {
        *res = T->data;
        T = T->right;
        free(min);
        return T;
    }

    T->left = getMinAndDelete(T->left, res);
    return T;
}

searchTree_t *delete_search_tree(myElement x, searchTree_t *T)
{
    searchTreePos_t *tmp;

    if (T == NULL) return NULL;

    if (x < T->data) T->left = delete_search_tree(x, T->left);
    else if (x > T->data) T->right = delete_search_tree(x, T->right);
    // 以下两种情况都是 x == T->data
    else if (T->left && T->right) {
        // 两个儿子
        // 用右子树中最小的结点代替这个结点，并且删除该最小结点，因为最小结点不可能有左儿子，所以删除就变成了删除没有左儿子的结点
        tmp = delete_get_min(&T->right);
        T->data = tmp->data;
        free(tmp);

        // 更直观的方式如下代码，用此时T的后继节点数据代替T数据后，问题转换为删除T右子树中最小结点的问题，且最小结点肯定没有左儿子
        // 但是search_tree_min和delete都对T右子树做了一次搜索，所以效率不如以上这种方式
        /*
        tmp = search_tree_min(T->right);
        T->data = tmp->data;
        T->right = delete(T->data, T->right);
        */
    } else {
        tmp = T;
        // 如果没有左儿子，则将右儿子代替T，不管右儿子是不是NIL
        if (T->left == NULL) T = T->right;
        // 如果没有右儿子，则将左儿子代替T
        else if (T->right == NULL) T = T->left;
        free(tmp);
    }

    return T;
}

int search_tree_height(searchTree_t *T)
{
    if (T == NULL) return 0;

    return MAX_INT(search_tree_height(T->left), search_tree_height(T->right)) + 1;
}

// 中序遍历
// 二叉搜索树的中序遍历就是递增序列
void in_order_walk(searchTree_t *T)
{
    if (T == NULL) {
        return;
    }

    in_order_walk(T->left);
    printf(" %d ", T->data);
    in_order_walk(T->right);
}

void BFS(searchTree_t *T)
{
    if (T == NULL) {
        return;
    }

    int head = 0;
    int tail = 0;
    searchTree_t* queue[MAX_NUM]; 
    queue[tail++] = T;

    while(head < tail) {
        searchTree_t* node = queue[head++];
        printf(" %d ", node->data);
        if (node->left != NULL) queue[tail++] = node->left;
        if (node->right != NULL) queue[tail++] = node->right;
    }
}

void printLevel(searchTree_t *T, int level)
{
    if (T == NULL) {
        if (level == 1) printf("NULL ");
    } else {
        if (level == 1) {
            printf("%d ", T->data);
        } else {
            printLevel(T->left, level - 1);
            printLevel(T->right, level - 1);
        }
    }
}

void search_tree_BFS_print(searchTree_t *T) {
    if (T == NULL) return;

    int height = search_tree_height(T);
    for (int i = 1; i <= height; i++) {
        printLevel(T, i);
        printf("\n");
    }
}

// 翻转二叉树
// 注意翻转后的二叉树不再是搜索二叉树，也就不具备原本的一些特性，以上函数都用不上了
searchTree_t* invertTree(searchTree_t* T)
{
    if (T == NULL) return NULL;

    searchTree_t *pl = T->left;

    T->left = invertTree(T->right);
    T->right = invertTree(pl);
    return T;
}