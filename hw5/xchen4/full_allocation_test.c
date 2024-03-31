// Author: Paprika Chen
// Test for use up all the memory initialized
// Right behavior: Fail the last allocation as expected

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define PAGE_SIZE 4096  

int main() {
    if (Mem_Init(PAGE_SIZE) != 0) {
        fprintf(stderr, "Mem_Init failed to initialize memory\n");
        return EXIT_FAILURE;
    }

    // Continuously allocate blocks of memory until allocation fails
    const int blockSize = 128;  // Size of each block to allocate
    int blocksAllocated = 0;
    while (1) {
        void* block = Mem_Alloc(blockSize);
        if (block == NULL) {
            break;  // Break the loop if allocation fails
        }
        blocksAllocated++;
    }

    if (blocksAllocated == 0) {
        fprintf(stderr, "Failed to allocate any blocks of size %d\n", blockSize);
        return EXIT_FAILURE;
    }

    printf("Successfully allocated %d blocks of %d bytes before running out of space.\n", blocksAllocated, blockSize);

    // allocate an additional block that has size >= previous allocation
    void* smallBlock = Mem_Alloc(130);
    if (smallBlock != NULL) {
        fprintf(stderr, "Succeeded in allocating additional memory when not expected.\n");
        return EXIT_FAILURE;
    }

    Mem_Dump();

    return EXIT_SUCCESS;
}
