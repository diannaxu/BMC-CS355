/**
 * 15_memory_after_alloc.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 15 - Check that memory can be written to after allocation.
 *
 * Expected Result:
 * Success: Aligned allocations test passed!
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

void memory_written_to_after_alloc() {
    void *ptr = Mem_Alloc(16);

    if (ptr != NULL) {
        memset(ptr, 'W', 16); // Writing to memory
        printf("Success: Memory can be written to after allocation test passed!\n");
        Mem_Free(ptr, 1);
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Memory can be written to after allocation test failed!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    memory_written_to_after_alloc(); // Test
    return 0;
}