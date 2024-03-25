/**
 * 13_no_space_alloc.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 13 - No space left to allocate.
 *
 * Expected Result:
 * Success: No space left to allocate test passed!
 */

#include <stdio.h>

#include "mem.h"

void no_space_left_to_alloc() {
    while (Mem_Alloc(64) != NULL);

    // Try to allocate more memory when no space is left.
    void *ptr = Mem_Alloc(64);
    if (ptr == NULL) {
        printf("Success: No space left to allocate test passed!\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: No space left to allocate test failed!\n");
        Mem_Free(ptr, 1);
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    no_space_left_to_alloc(); // Test
    return 0;
}