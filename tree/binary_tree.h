#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "tree.h"

typedef struct searchTreeNode searchTree_t;
typedef struct searchTreeNode searchTreePos_t;

typedef struct searchTreeNode
{
    myElement data; // use int for data
    struct searchTreeNode *left;
    struct searchTreeNode *right;
} searchTreeNode_t;

searchTree_t *search_tree_insert(myElement x, searchTree_t *T);
void destroy_search_tree(searchTree_t *T);
searchTreePos_t *search_tree_search(searchTree_t *T, myElement k);
searchTreePos_t *search_tree_min(searchTree_t *T);searchTreePos_t *search_tree_max(searchTree_t *T);
searchTree_t *delete_search_tree(myElement x, searchTree_t *T);
int search_tree_height(searchTree_t *T);
void in_order_walk(searchTree_t *T);
void search_tree_BFS_print(searchTree_t *T);
void BFS(searchTree_t *T);
searchTree_t* invertTree(searchTree_t* T);

#endif