// Author: Paprika Chen
// Test for odd allocation and free.
// Right behavior: print: print: Memory cleanup successful. 

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize a block of memory for testing
    if (Mem_Init(2000) != 0) {
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }

    void* block1 = Mem_Alloc(75);  
    void* block2 = Mem_Alloc(123); 
    void* block3 = Mem_Alloc(189); 

    // Verify each block is allocated
    void* blocks[] = {block1, block2, block3};
    for (int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); i++) {
        if (blocks[i] == NULL) {
            fprintf(stderr, "Mem_Alloc failed to allocate\n");
            return EXIT_FAILURE;
        }
        printf("Successfully allocated odd-sized block at %p\n", blocks[i]);
    }

    // Free some of the allocated blocks
    if (Mem_Free(block1, 0) != 0) { // Adjust the second argument as per your implementation
        fprintf(stderr, "Mem_Free failed for block1\n");
        return EXIT_FAILURE;
    }

    if (Mem_Free(block2, 0) != 0) {
        fprintf(stderr, "Mem_Free failed for block2\n");
        return EXIT_FAILURE;
    }

    if (Mem_Free(block3, 0) != 0) {
        fprintf(stderr, "Mem_Free failed for block3\n");
        return EXIT_FAILURE;
    }

    printf("Memory cleanup successful. \n");
    return EXIT_SUCCESS;
}
