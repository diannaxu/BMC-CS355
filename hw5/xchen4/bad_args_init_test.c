// Author: Paprika Chen
// Test for bad args to Mem_Init()
// Right behavior: print: 
// Mem_Init correctly failed with size 0
// Mem_Init correctly failed with negative size

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Test with size 0
    if (Mem_Init(0) == 0) {
        fprintf(stderr, "Mem_Init should fail with size 0\n");
        return EXIT_FAILURE;
    } else {
        printf("Mem_Init correctly failed with size 0\n");
    }

    // Test with negative size
    if (Mem_Init(-6) == 0) {
        fprintf(stderr, "Mem_Init should fail with negative size\n");
        return EXIT_FAILURE;
    } else {
        printf("Mem_Init correctly failed with negative size\n");
    }

    return EXIT_SUCCESS;
}
