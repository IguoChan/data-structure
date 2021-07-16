#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "list.h"
#include "list_sentinel.h"

list_t *l = NULL;
list_s_t *ls = NULL;

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

void test_list_s_create()
{
    ls = list_s_create();
    list_s_print(ls);
}

void test_list_s_append()
{    
    int *data;
    int ret;
    for (int i = 0; i < 5; i++) {
        data = malloc(sizeof(int));
        *data = i;
        ret = list_s_append(ls, data);
        if (ret < 0) CU_FAIL("APPEND FAIL!");
    }    
    list_s_print(ls);
}
void test_list_s_prepend()
{    
    int *data;
    int ret;
    for (int i = 0; i < 5; i++) {
        data = malloc(sizeof(int));
        *data = i;
        ret = list_s_prepend(ls, data);
        if (ret < 0) CU_FAIL("PREPEND FAIL!");
    }    
    list_s_print(ls);
}

void test_list_s_insert_at()
{
    int *data;
    int ret;
    data = malloc(sizeof(int));
    *data = 100;
    ret = list_s_insert_at(ls, 100, data);
    if (ret < 0) printf("INSERT FAIL!\n");
    ret = list_s_insert_at(ls, 5, data);
    if (ret < 0) CU_FAIL("PREPEND FAIL!");
    list_s_print(ls);
}

void test_list()
{
    test_list_create();
    test_list_append();
    test_list_prepend();
    test_list_insert_at();
}

void test_s_list()
{
    test_list_s_create();
    test_list_s_append();
    test_list_s_prepend();
    test_list_s_insert_at();
}

int main(int argc, char * argv[])
{
    test_list();
    test_s_list();
    // CU_PASS("LIST TEST SUCCESS!");
}