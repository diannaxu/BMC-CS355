// Author: Paprika Chen
// Test for coalesce locally
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

    printf("\ncoalesce locally for block2, shouldn't trigger any coalescing.\n");
    printf("Should have two free blocks in total.\n");
    if (Mem_Free(block2, 2) != 0) {
         fprintf(stderr, "Mem_Free failed\n");
         return EXIT_FAILURE;
     }
    Mem_Dump(); 

    printf("\ncoalesce locally for block1, should coalesce with block2. \n");
    printf("Therefore, should still have two free chunks in total.\n");
    if (Mem_Free(block1, 2) != 0) {
         fprintf(stderr, "Mem_Free failed\n");
         return EXIT_FAILURE;
     }
    Mem_Dump();

    printf("\ncoalesce locally for block3, should coalesce with the previous block. \n");
    printf("Therefore, should still have one free chunks in total.\n");
    // Cleanup
    if (Mem_Free(block3, 2) != 0) {
        fprintf(stderr, "Error freeing memory during cleanup.\n");
        return EXIT_FAILURE;
    }
    Mem_Dump();


    printf("Memory cleanup successful. Coalescing test completed.\n");
    return EXIT_SUCCESS;
}