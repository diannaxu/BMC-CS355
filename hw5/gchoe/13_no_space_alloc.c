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
#include <stdlib.h>

#include "mem.h"

// Global variable
int mem_size = 1024;

void no_space_left_to_alloc() {
    // Try to allocate more memory than there is space.
    void *ptr = Mem_Alloc(mem_size + 1);

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
    if (Mem_Init(mem_size) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    no_space_left_to_alloc(); // Test
    return 0;
}