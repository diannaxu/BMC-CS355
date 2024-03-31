// Author: Paprika Chen
// Test for a simple 8-byte allocation.
// Right behavior: print: Nothing is printed.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize memory region
    if (Mem_Init(1024) != 0) {
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }
    printf("mem_init success\n");
    // Allocate 8 bytes of memory
    void* ptr = Mem_Alloc(8);
    if (ptr == NULL) {
        fprintf(stderr, "Mem_Alloc failed\n");
        return EXIT_FAILURE;
    }

    Mem_Dump();

    return EXIT_SUCCESS;
}
