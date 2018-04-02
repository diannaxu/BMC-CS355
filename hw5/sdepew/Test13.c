#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../list.h"
#include "../../boolean.h"
#include "../../helper.h"
#include "../../mem.h"

/*
 * Testing for no space left to allocate
 * Expected Behavior: Should should only one block of memory on dump at end and have it be freed, should have one page of memory
 */
int test_thirteen() {
    if (Mem_Init(getpagesize()) == ERROR) {
        return EXIT_FAILURE;
    }
    Mem_Dump();

    void *allocated = Mem_Alloc(getpagesize());
    if (allocated == NULL) {
        return EXIT_FAILURE;
    }
    printf("after first allocated\n");
    Mem_Dump();

    //attempt to allocate a page that you do not have in memory
    void *allocated2 = Mem_Alloc(getpagesize());
    if (allocated2 != NULL) {
        return EXIT_FAILURE;
    }

    if (Mem_Free(allocated, TRUE) == ERROR) {
        return EXIT_FAILURE;
    }
    printf("after first freed\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}

int main() {
    return (test_thirteen());
}