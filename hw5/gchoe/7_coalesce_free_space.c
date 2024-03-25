/**
 * 7_coalesce_free_space.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 7 - Coalesce of free space.
 *
 * Expected Result:
 * Success: Coalesce free space test passed!
 */

#include <stdio.h>

#include "mem.h"

void coalesce_free_space() {
    void *ptr1 = Mem_Alloc(32);
    void *ptr2 = Mem_Alloc(64);
    void *ptr3 = Mem_Alloc(128);

    // Free some ptr's
    Mem_Free(ptr1, 1);
    Mem_Free(ptr3, 1);

    // Allocate memory
    void *ptr4 = Mem_Alloc(64);

    // Check if coalescing of free space is happening properly
    if (ptr4 != NULL) {
        printf("Success: Coalesce free space test passed!\n");
        Mem_Free(ptr2, 1);
        Mem_Free(ptr4, 1);
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Coalesce free space test failed!\n");
        Mem_Free(ptr2, 1);
        Mem_Free(ptr4, 1);
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(2048) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    coalesce_free_space(); // Test
    return 0;
}