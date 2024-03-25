// Author: Paprika Chen
// Test for simple allocation and free.
// Right behavior: print: Nothing is printed.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize a block of memory
    if (Mem_Init(1024) != 0) {
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }

    // Allocate a small block of memory
    void* block = Mem_Alloc(128); 
    if (block == NULL) {
        fprintf(stderr, "Mem_Alloc failed to allocate 128 bytes\n");
        return EXIT_FAILURE;
    } 

    // Free the allocated block
    if (Mem_Free(block, 0) != 0) { 
        fprintf(stderr, "Mem_Free failed\n");
        return EXIT_FAILURE;
    } 

    return EXIT_SUCCESS;
}
