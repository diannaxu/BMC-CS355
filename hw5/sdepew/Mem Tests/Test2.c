//
// Created by Sarah Depew on 3/26/18.
//

#include "../../mem.h"
#include "../../helper.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_ALLOC 8

/*
 * Testing for 8-byte alignment with 8 byte allocation
 * Expected Behavior: Should see 8-byte alignment on dump printout
 */
int test_two() {
    int result = Mem_Init(NUM_ALLOC);
    if(result == ERROR) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    void *resultPtr = Mem_Alloc(NUM_ALLOC);
    if(resultPtr == NULL) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    result = Mem_Free(resultPtr, 0);
    if(result == ERROR) {
        return EXIT_FAILURE;
    } else {
        Mem_Dump();
    }

    return EXIT_SUCCESS;
}


int main() {
    exit(test_two());
}
