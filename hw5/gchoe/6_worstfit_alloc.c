/**
 * 6_worstfit_alloc.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 6 - Worstfit allocation.
 *
 * Expected Result:
 * Success: Worstfit allocation test passed!
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

void worstfit_alloc() {
    void *ptr1 = Mem_Alloc(16);
    void *ptr2 = Mem_Alloc(32);
    void *ptr3 = Mem_Alloc(64);
    void *ptr4 = Mem_Alloc(128);
    bool success = true;

    if ((ptr1 != NULL) && (ptr2 != NULL) && (ptr3 != NULL) && (ptr4 != NULL)) {
        printf("Success: Worstfit allocation test passed!\n");
    } else {
        printf("FAILURE: Worstfit allocation test failed!\n");
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
    if (Mem_Init(2048) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    worstfit_alloc(); // Test
    return 0;
}