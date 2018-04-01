#include <stdio.h>
#include <stdlib.h>
#include "../../list.h"
#include "../../boolean.h"
#include "../../helper.h"
#include "../../mem.h"

/*
 * Testing for coalescing of free space
 * Expected Behavior: Should should only one block of memory on dump at end
 */
int test_seven() {
    if (Mem_Init(16) == ERROR) {
        return EXIT_FAILURE;
    }

    Mem_Dump();

    void *allocated = Mem_Alloc(1);
    if (allocated == NULL) {
        return EXIT_FAILURE;
    }

    void *allocated2 = Mem_Alloc(7);
    if (allocated2 == NULL) {
        return EXIT_FAILURE;
    }

    void *allocated3 = Mem_Alloc(8);
    if (allocated3 == NULL) {
        return EXIT_FAILURE;
    }

    if (Mem_Free(allocated, TRUE) == ERROR) {
        return EXIT_FAILURE;
    }
    printf("after first freed\n");
    Mem_Dump();

    Mem_Dump();
    if (Mem_Free(allocated2, TRUE) == ERROR) {
        return EXIT_FAILURE;
    }
    printf("after second freed\n");
    Mem_Dump();


    if (Mem_Free(allocated3, TRUE) == ERROR) {
        return EXIT_FAILURE;
    }
    printf("after third freed\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}

int main() {
    return (test_seven());
}