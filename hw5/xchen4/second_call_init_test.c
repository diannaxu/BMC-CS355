// Author: Paprika Chen
// Test if the second call of Mem_Init() will fail
// Right behavior: print: Second call to Mem_Init failed as expected.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // First call to Mem_Init
    if (Mem_Init(1024) != 0) {
        fprintf(stderr, "Mem_Init failed on first call\n");
        return EXIT_FAILURE;
    }
    
    // Second call to Mem_Init, should fail
    if (Mem_Init(1024) == 0) {
        fprintf(stderr, "Second call to Mem_Init should fail, but it succeeded\n");
        return EXIT_FAILURE;
    }
    
    printf("Second call to Mem_Init failed as expected.\n");
    return EXIT_SUCCESS;
}
