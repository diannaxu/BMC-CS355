// Author: Paprika Chen
// Test for worst_fit allocation.
// Right behavior: print 2 pointers, they should be the same.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize a block of memory sufficiently large for the test
    if (Mem_Init(1792) != 0) {
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }

    void* first = Mem_Alloc(512); // Smaller block
    void* second = Mem_Alloc(1024); // Larger block, to be freed later
    printf("The second pointer is at %p\n", second);
    void* third = Mem_Alloc(256); // Smaller block

    // Check for allocation failure
    if (!first || !second || !third) {
        fprintf(stderr, "Initial allocations failed\n");
        return EXIT_FAILURE;
    }

    // Free the second block to create a large gap in the memory
    if (Mem_Free(second, 1) != 0) {
        fprintf(stderr, "Mem_Free failed\n");
        return EXIT_FAILURE;
    }

    // For a worst fit strategy, this should be allocated in the space freed by 'second'.
    void* worstFit = Mem_Alloc(768); // This size is chosen based on the gap created

    if (!worstFit) {
        fprintf(stderr, "Worst fit allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("The new pointer is at %p, should be the same as the second pointer\n", worstFit);

    return EXIT_SUCCESS;
}