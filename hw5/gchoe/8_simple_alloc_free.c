/**
 * 8_simple_alloc_free.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 8 - Simple allocation and free.
 *
 * Expected Result:
 * Success: Simple allocation and free test passed!
 */

#include <stdio.h>

#include "mem.h"

void simple_alloc_free() {
    void *ptr = Mem_Alloc(8); // Allocate memory

    if (ptr != NULL) {
        printf("Success: Simple allocation and free test passed!\n");
        Mem_Free(ptr, 1);
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Simple allocation and free test failed!\n");
        exit(EXIT_FAILURE);
    }
}


int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    simple_alloc_free(); // Test
    return 0;
}