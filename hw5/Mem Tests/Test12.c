#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../list.h"
#include "../../boolean.h"
#include "../../helper.h"
#include "../../mem.h"

/*
 * Testing for simple less than a page byte allocation and free
 * Expected Behavior: Should should only one block of memory on dump at end and have it be freed, should have one page of memory
 */
int test_twelve() {
    if (Mem_Init(1) == ERROR) {
        return EXIT_FAILURE;
    }
    Mem_Dump();

    void *allocated = Mem_Alloc(1);
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
    return (test_twelve());
}