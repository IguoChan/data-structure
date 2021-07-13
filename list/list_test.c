#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

#include "list.h"
#include "list_sentinel.h"

list_t *l = NULL;

void test_list_create()
{
    l = list_s_create();
    list_print(l);
}

void test_list_append()
{
    int *data;
    int ret;
    for (int i = 0; i < 10; i++, data++) {
        data = malloc(sizeof(int));
        *data = 10 - i;
        ret = list_s_append(l, data);
        if (ret < 0) CU_FAIL("APPEND FAIL!");
    }    
    list_s_print(l);
}

int main(int argc, char * argv[])
{
    test_list_create();
    test_list_append();
    // CU_PASS("LIST TEST SUCCESS!");
}