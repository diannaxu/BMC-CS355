// Author: Paprika Chen
// Test for coalesce globally and then coalesce locally
// Right behavior: first perform as the printf describes
// then print: Memory cleanup successful. Coalescing test completed.

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
    void* block1 = Mem_Alloc(8); 
    void* block2 = Mem_Alloc(8);
    void* block3 = Mem_Alloc(8);
    Mem_Dump(); 

    printf("\ncoalesce globally for block2, should perform no coalscing and have two free chunks.\n");
    if (Mem_Free(block2, 1) != 0) {
        fprintf(stderr, "Mem_Free failed\n");
        return EXIT_FAILURE;
    }
    Mem_Dump(); 

    printf("\nfree block 1 and then free block 3 with global coalescing. Should have 1 free chunk.\n");
    if (Mem_Free(block1, 0) != 0 || Mem_Free(block3,1) != 0) {
        fprintf(stderr, "Mem_Free failed\n");
        return EXIT_FAILURE;
    }

    void* block4 = Mem_Alloc(8);
    void* block5 = Mem_Alloc(500);
    Mem_Dump();
    printf("\nfree block 4 and then free block 5 with neighbor coalescing. Should have 1 free chunk.\n");
    if (Mem_Free(block4, 0) != 0 || Mem_Free(block5,2) != 0) {
        fprintf(stderr, "Mem_Free failed\n");
        return EXIT_FAILURE;
    }
    Mem_Dump();

    printf("Memory cleanup successful. Coalescing test completed.\n");
    return EXIT_SUCCESS;
}