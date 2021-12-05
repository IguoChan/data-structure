#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "queue.h"
#include "priority_queue.h"

void test_priority_queue()
{
    pQueue_t *H = pQueue_initialize(1000);
    if (!H) CU_FAIL("pQueue_initialize FAIL!");
    pQueue_print(H);

    int ret;
    ret = pQueue_insert(H, 13);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 21);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 16);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 24);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 31);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 19);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 68);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 65);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 26);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    ret = pQueue_insert(H, 32);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");

    ret = pQueue_insert(H, 14);
    if (ret < 0) CU_FAIL("pQueue_insert FAIL!");
    pQueue_print(H);

    MyElement x = pQueue_get_and_delete_min(H);
    printf("min: %d\n", x);
    pQueue_print(H);
}

int main(int argc, char * argv[])
{
    // test_binary_tree_insert();
    test_priority_queue();
    return 0;
}