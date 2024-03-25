/**
 * 3_aligned_alloc.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 3 - A few aligned allocations.
 *
 * Expected Result:
 * Success: Aligned allocations test passed!
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "mem.h"

void aligned_allocs() {
    int i = 0;
    bool success = true;
    void *ptr[3]; // Array to store pointers for freeing later

    while (i < 3) {
        ptr[i] = Mem_Alloc(3);
        
        // Check alignment of the pointer
        if ((uintptr_t)ptr % 3 != 0) {
            success = false;
        }

        i++;
    }

    // Free
    for (int j = 0; j < 3; j++) {
        Mem_Free(ptr[j], 1);
    }

    if (success) {
        printf("Success: Aligned allocations test passed!\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Aligned allocations test failed!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init().\n");
        exit(EXIT_FAILURE);
    }

    aligned_allocs(); // Test
    return 0;
}