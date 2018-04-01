//
// Created by Sarah Depew on 3/26/18.
//

#include "../../mem.h"
#include "../../helper.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_ALLOC 8

/*
 * Testing for aligned allocations
 * Expected Behavior: Should see 8-byte alignment on dump printout
 */
int test_three() {
    int result = Mem_Init(NUM_ALLOC + NUM_ALLOC * 2 + NUM_ALLOC * 8);
    if (result == ERROR) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    void *resultPtr = Mem_Alloc(NUM_ALLOC);
    if (resultPtr == NULL) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    void *resultPtr2 = Mem_Alloc(NUM_ALLOC * 2);
    if (resultPtr == NULL) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    void *resultPtr3 = Mem_Alloc(NUM_ALLOC * 8);
    if (resultPtr == NULL) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    result = Mem_Free(resultPtr, 0);
    if (result == ERROR) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    result = Mem_Free(resultPtr2, 0);
    if (result == ERROR) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    result = Mem_Free(resultPtr3, 1);
    if (result == ERROR) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    return EXIT_SUCCESS;
}


int main() {
    exit(test_three());
}
