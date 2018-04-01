#include <stdio.h>
#include <stdlib.h>
#include "../../list.h"
#include "../../boolean.h"
#include "../../helper.h"
#include "../../mem.h"

/*
 * Testing for simple aligned byte allocation and free
 * Expected Behavior: Should should only one block of memory on dump at end and have it be freed, block should be 64 when allocated
 */
int test_nine() {
    if (Mem_Init(64) == ERROR) {
        return EXIT_FAILURE;
    }
    Mem_Dump();

    void *allocated = Mem_Alloc(64);
    if (allocated == NULL) {
        return EXIT_FAILURE;
    }
    printf("after first allocated\n");
    Mem_Dump();

    if (Mem_Free(allocated, TRUE) == ERROR) {
        return EXIT_FAILURE;
    }
    printf("after first freed\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}

int main() {
    return (test_nine());
}