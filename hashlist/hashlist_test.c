#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "hashlist.h"

hashlist_int_t *hli;
const int intkey[10] = {1, 11, 111, 2, 22, 222, 3, 33, 333, 4};

void test_hashlist_create_int()
{
    hli = hashlist_create_int();
}

void test_hashlist_add_int()
{
    int *data, *out;
    int ret;
    for (int i = 0; i < 10; i++)
    {
        data = (int*)malloc(sizeof(int));
        *data = i;
        ret = hashlist_add_int(hli, intkey[i], data);
        if (ret < 0) CU_FAIL("ADD INT FAIL!\n");
    }    
}

void test_hashlist_find_int()
{
    int key, *data;
    for (int i = 0; i < 10; i++)
    {
        key = intkey[9-i];
        data = (int *)hashlist_find_int(hli, key);
        if (!data) {
            printf("find key:%d failed!", key);
        } else {
            printf("key: %d, value: %d\n", key, *data);
        }
    }
}

void test_hashlist_delete_int()
{
    int *data;
    int key = intkey[3];
    int ret = hashlist_delete_int(hli, key);
    if (ret < 0) CU_FAIL("DELETE FAIL!\n");
    for (int i = 0; i < 10; i++)
    {
        key = intkey[i];
        data = (int *)hashlist_find_int(hli, key);
        if (!data) {
            printf("find key:%d failed!\n", key);
        } else {
            printf("key: %d, value: %d\n", key, *data);
        }
    }
}

void test_hashlist_destroy_int()
{
    int key, *data;
    int ret = hashlist_destroy_int(hli);
    if (ret < 0) CU_FAIL("DESTROY FAIL!\n");
    for (int i = 0; i < 10; i++)
    {
        key = intkey[i];
        data = (int *)hashlist_find_int(hli, key);
        if (!data) {
            printf("find key:%d failed!\n", key);
        } else {
            printf("key: %d, value: %d\n", key, *data);
        }
    }
}

int main(int argc, char * argv[])
{
    test_hashlist_create_int();
    test_hashlist_add_int();
    test_hashlist_find_int();
    test_hashlist_delete_int();
    // test_hashlist_destroy_int();
    // CU_PASS("LIST TEST SUCCESS!");
}