/**
 * 4_odd_size_alloc.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 4 - Several odd-sized allocations.
 *
 * Expected Result:
 * Success: Odd-sized allocations test passed!
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mem.h"

void odd_sized_allocs() {
    void *ptr1 = Mem_Alloc(7);
    void *ptr2 = Mem_Alloc(13);
    void *ptr3 = Mem_Alloc(21);
    void *ptr4 = Mem_Alloc(25);
    bool success = true;

    if ((ptr1 != NULL) && (ptr2 != NULL) && (ptr3 != NULL) && (ptr4 != NULL)) {
        printf("Success: Odd-sized allocations test passed!\n");
    } else {
        printf("FAILURE: Odd-sized allocations test failed!\n");
        success = false;
    }

    // Free appropriattely
    if (ptr1 != NULL) {
        Mem_Free(ptr1, 1);
    }

    if (ptr2 != NULL) {
        Mem_Free(ptr2, 1);
    }

    if (ptr3 != NULL) {
        Mem_Free(ptr3, 1);
    }

    if (ptr4 != NULL) {
        Mem_Free(ptr4, 1);
    }

    if (success) {
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init().\n");
        exit(EXIT_FAILURE);
    }

    odd_sized_allocs(); // Test
    return 0;
}