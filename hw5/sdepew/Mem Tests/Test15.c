#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../list.h"
#include "../../boolean.h"
#include "../../helper.h"
#include "../../mem.h"

/*
 * Testing for simple ability to write to memory
 * Expected Behavior: Should should only one block of memory on dump at end and have it be freed, should have one page of memory
 */
int test_fifteen() {
    if (Mem_Init(sizeof(int *)) == ERROR) {
        return EXIT_FAILURE;
    }
    Mem_Dump();

    int *allocated = (int *) Mem_Alloc(sizeof(int *));
    if (allocated == NULL) {
        return EXIT_FAILURE;
    }
    printf("after first allocated\n");
    Mem_Dump();

    *allocated = 12;
    printf("contents of allocated: %d\n", *allocated);

    if (Mem_Free(allocated, TRUE) == ERROR) {
        return EXIT_FAILURE;
    }
    printf("after first freed\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}

int main() {
    return (test_fifteen());
}