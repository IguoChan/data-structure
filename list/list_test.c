#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "doubly_linked_list.h"
#include "circular_linked_list.h"

list_t *l = NULL;

void test_list_create()
{
    l = list_create();
    list_print(l);
}

void test_list_append()
{
    int *data;
    int ret;
    for (int i = 0; i < 5; i++) {
        data = malloc(sizeof(int));
        *data = i;
        ret = list_append(l, data);
        if (ret < 0) CU_FAIL("APPEND FAIL!");
    }    
    list_print(l);
}

void test_list_prepend()
{
    int *data;
    int ret;
    for (int i = 0; i < 5; i++) {
        data = malloc(sizeof(int));
        *data = i;
        ret = list_prepend(l, data);
        if (ret < 0) CU_FAIL("PREPEND FAIL!");
    }
    list_print(l);
}

void test_list_insert_at()
{
    int *data;
    int ret;
    data = malloc(sizeof(int));
    *data = 100;
    ret = list_insert_at(l, 100, data);
    if (ret < 0) printf("INSERT FAIL!\n");
    ret = list_insert_at(l, 5, data);
    if (ret < 0) CU_FAIL("PREPEND FAIL!");
    list_print(l);
}

void test_list_retrieve_data_at()
{
    int *data;

    data = (int *)list_retrieve_data_at(l, 10);
    if (!data) printf("GET FAIL!\n");
    list_print(l);
}

void test_list_remove_data()
{
    int *data;
    int ret;
    data = malloc(sizeof(int));
    *data = 200;
    ret = list_insert_at(l, 3, data);
    if (ret < 0) CU_FAIL("insert FAIL!");
    list_print(l);
    ret = list_remove_data(l, data);
    if (ret < 0) CU_FAIL("REMOVE FAIL!");
    list_print(l);
}

int main(int argc, char * argv[])
{
    test_list_create();
    test_list_append();
    // test_list_prepend();
    // test_list_insert_at();
    // test_list_retrieve_data_at();
    test_list_remove_data();
    // CU_PASS("LIST TEST SUCCESS!");
}