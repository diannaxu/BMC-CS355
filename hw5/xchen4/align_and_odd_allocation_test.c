// Author: Paprika Chen
// Test for Aligned and Odd-Sized Allocations.
// Right behavior: print: Nothing is printed.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize memory region
    if (Mem_Init(4096) != 0) { 
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }

    // Define an array of sizes 
    long sizes[] = {8, 15, 24, 33, 42, 7, 16, 25};
    // calculate the size of the array
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        void* ptr = Mem_Alloc(sizes[i]);
        if (ptr == NULL) {
            fprintf(stderr, "Mem_Alloc failed for size %ld\n", sizes[i]);
            return EXIT_FAILURE;
        }

        // Check 8-byte alignment
        if ((unsigned long)ptr % 8 != 0) {
            fprintf(stderr, "Memory is not 8-byte aligned for size %ld: %p\n", sizes[i], ptr);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
