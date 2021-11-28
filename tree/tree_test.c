#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "binary_tree.h"
#include "rb_tree.h"

void test_binary_tree_insert()
{
    searchTree_t *T = NULL;
    // myElement datas[6] = {5, 3, 6, 2, 4, 7};
    // for(int i = 0; i < 6; i++) {
    //     T = search_tree_insert(datas[i], T);
    //     if (T == NULL) CU_FAIL("INSERT FAIL!");
    // }
    // printf("height = %d\n", search_tree_height(T));
    // // in_order_walk(T);
    // search_tree_BFS_print(T);
    // printf("\n~~~~~~\n");

    // searchTree_t *T1 = invertTree(T);
    // search_tree_BFS_print(T1);
    // printf("\n~~~~~~\n");
    // search_tree_BFS_print(T);
    // printf("\n~~~~~~\n");

    // T = delete_search_tree(3, T);
    // search_tree_BFS_print(T);
    // printf("\n~~~~~~\n");
    for (myElement i = 10; i > 0; i--) {
        T = search_tree_insert(i, T);
    }
    search_tree_BFS_print(T);
}

void test_rbtree_insert()
{
    rbTree_t *T = rbtree_init();
    // for (myElement i = 10; i > 0; i--) {
    //     rbtree_insert(T, i);
    // }

    // for (myElement i = 30; i > 10; i--) {
    //     rbtree_insert(T, i);
    // }
    myElement datas[14] = {10,85,15,70,20,60,30,50,65,80,90,40,5,55};
    for (int i = 0; i < 14; i++) rbtree_insert(T, datas[i]);

    
    rbtree_BSF_print(T);
}

int main(int argc, char * argv[])
{
    // test_binary_tree_insert();
    test_rbtree_insert();
    return 0;
}