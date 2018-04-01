#include <stdio.h>
#include <stdlib.h>
#include "../../list.h"
#include "../../boolean.h"
#include "../../helper.h"
#include "../../mem.h"

/*
 * Testing for simple odd byte allocation and free
 * Expected Behavior: Should should only one block of memory on dump at end and have it be freed, block should be 16 bytes when allocated and then proper page size when freed
 */
int test_ten() {
    if (Mem_Init(13) == ERROR) {
        return EXIT_FAILURE;
    }
    Mem_Dump();

    void *allocated = Mem_Alloc(13);
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
    return (test_ten());
}