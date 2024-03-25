/**
 * 9_aligned_alloc_free.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 9 - Aligned allocation and free.
 *
 * Expected Result:
 * Success: Aligned allocation and free test passed!
 */

#include <stdio.h>

#include "mem.h"

void aligned_alloc_free() {
    void *ptr = Mem_Alloc(8);
    
    if ((uintptr_t)ptr % 8 == 0) {
        printf("Success: Aligned allocation and free test passed!\n");
        Mem_Free(ptr, 1);
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Aligned allocation and free test failed!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    aligned_alloc_free();
    return 0;
}