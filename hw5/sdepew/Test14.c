#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../list.h"
#include "../../boolean.h"
#include "../../helper.h"
#include "../../mem.h"

/*
 * Testing for freeing a NULL pointer
 * Expected Behavior: Should should only one block of memory on dump at end and have it be freed, should have one page of memory and no memory should be allocated
 */
int test_fourteen() {
    if (Mem_Init(1) == ERROR) {
        return EXIT_FAILURE;
    }
    Mem_Dump();

    void *allocated = NULL;

    //expected behavior: nothing happens
    if (Mem_Free(allocated, FALSE) == ERROR) {
        return EXIT_FAILURE;
    }
    printf("after first freed\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}

int main() {
    return (test_fourteen());
}