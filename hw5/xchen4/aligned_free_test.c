// Author: Paprika Chen
// Test for aligned allocation and free.
// Right behavior: print: print: Successfully freed the allocated blocks

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize a memory
    if (Mem_Init(4096) != 0) {
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }

    // Allocate multiple blocks of memory, each expected to be aligned
    void* block1 = Mem_Alloc(64); // Allocate 64 bytes
    void* block2 = Mem_Alloc(128); // Allocate 128 bytes
    void* block3 = Mem_Alloc(256); // Allocate 256 bytes

    // Verify each block is allocated and aligned
    void* blocks[] = {block1, block2, block3};
    for (int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); i++) {
        if (blocks[i] == NULL) {
            fprintf(stderr, "Mem_Alloc failed to allocate\n");
            return EXIT_FAILURE;
        }
        if ((unsigned long)blocks[i] % 8 != 0) { // Check for 8-byte alignment
            fprintf(stderr, "Allocation is not aligned: %p\n", blocks[i]);
            return EXIT_FAILURE;
        }
    }

    // Free some of the allocated blocks
    if (Mem_Free(block1, 0) != 0) { 
        fprintf(stderr, "Mem_Free failed for block1\n");
        return EXIT_FAILURE;
    }

    if (Mem_Free(block2, 0) != 0) {
        fprintf(stderr, "Mem_Free failed for block3\n");
        return EXIT_FAILURE;
    }

    if (Mem_Free(block3, 0) != 0) {
        fprintf(stderr, "Mem_Free failed for block3\n");
        return EXIT_FAILURE;
    }

    printf("Successfully freed the allocated blocks\n");
}