// Author: Paprika Chen
// Test for coalesce of free adjacent space
// Right behavior: print: Memory cleanup successful. Coalescing test completed.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

int main() {
    // Initialize a block of memory for the test
    if (Mem_Init(3072) != 0) {
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }

    // Allocate several blocks of memory
    void* block1 = Mem_Alloc(1024); 
    void* block2 = Mem_Alloc(1024); 
    void* block3 = Mem_Alloc(1024); 

    if (!block1 || !block2 || !block3) {
        fprintf(stderr, "Initial allocations failed\n");
        return EXIT_FAILURE;
    }

    // Free the first and second blocks
    if (Mem_Free(block1, 0) != 0 || Mem_Free(block2, 0) != 0) {
        fprintf(stderr, "Mem_Free failed\n");
        return EXIT_FAILURE;
    }

    // attempt to coalesce adjacent free blocks
    if (Mem_Free(NULL, 1) != 0) { // Use appropriate call for your implementation
        fprintf(stderr, "Coalescing failed\n");
        return EXIT_FAILURE;
    }

    // Attempt to allocate a block that fits into the coalesced space
    void* largeBlock = Mem_Alloc(2048); // Should fit if coalescing worked
    if (!largeBlock) {
        fprintf(stderr, "Failed to allocate memory in coalesced space\n");
        return EXIT_FAILURE;
    }

    // Cleanup
    if (Mem_Free(block2, 0) != 0 || Mem_Free(largeBlock, 0) != 0) {
        fprintf(stderr, "Error freeing memory during cleanup.\n");
        return EXIT_FAILURE;
    }

    printf("Memory cleanup successful. Coalescing test completed.\n");
    return EXIT_SUCCESS;
}
