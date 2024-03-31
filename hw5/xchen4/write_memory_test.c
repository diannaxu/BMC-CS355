// Author: Paprika Chen
// Test for write on allocated memory
// Right behavior: print: Successfully wrote to and read from the allocated memory.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize the memory 
    if (Mem_Init(1024) != 0) { 
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }

    // Allocate a block of memory
    int blockSize = 256; 
    int* block = (int*)Mem_Alloc(blockSize);
    if (block == NULL) {
        fprintf(stderr, "Mem_Alloc failed to allocate the requested memory\n");
        return EXIT_FAILURE;
    }

    // Write to the allocated memory
    int numElements = blockSize / sizeof(int); 
    for (int i = 0; i < numElements; i++) {
        block[i] = i; // Store each element's index as its value
    }

    // Verify the written values
    for (int i = 0; i < numElements; i++) {
        if (block[i] != i) {
            return EXIT_FAILURE;
        }
    }

    printf("Successfully wrote to and read from the allocated memory.\n");

    // Cleanup
    if (Mem_Free(block, 0) != 0) { 
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
