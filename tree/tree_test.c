#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "binary_tree.h"

void test_binary_tree_insert()
{
    searchTree_t *T = NULL;
    myElement datas[6] = {5, 3, 6, 2, 4, 7};
    for(int i = 0; i < 6; i++) {
        T = search_tree_insert(datas[i], T);
        if (T == NULL) CU_FAIL("INSERT FAIL!");
    }
    printf("height = %d\n", search_tree_height(T));
    // in_order_walk(T);
    BFS_print(T);
    printf("\n~~~~~~\n");

    searchTree_t *T1 = invertTree(T);
    BFS_print(T1);
    printf("\n~~~~~~\n");
    BFS_print(T);
    printf("\n~~~~~~\n");

    T = delete_search_tree(3, T);
    BFS_print(T);
    printf("\n~~~~~~\n");
}

int main(int argc, char * argv[])
{
    test_binary_tree_insert();
    return 0;
}