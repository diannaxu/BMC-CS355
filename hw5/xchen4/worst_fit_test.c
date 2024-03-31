// Author: Paprika Chen
// Test for worst_fit allocation strategy.
// Right behavior: The printed biggest free chunk should continuously decreases because it is chosen.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize a block of memory sufficiently large for the test
    if (Mem_Init(3000) != 0) {
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }
    Mem_Dump();

    void* first = Mem_Alloc(512); 
    if (Mem_Free(first,0)== -1) {
        return EXIT_FAILURE;
    };
    Mem_Dump();
    void* second = Mem_Alloc(512); 
    Mem_Dump();
    void* third = Mem_Alloc(256);
    Mem_Dump();
    void* fourth = Mem_Alloc(256);
    Mem_Dump();

    // Check for allocation failure
    if (!first || !second || !third) {
        fprintf(stderr, "Initial allocations failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}