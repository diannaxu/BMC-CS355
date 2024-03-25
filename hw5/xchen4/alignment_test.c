// Author: Paprika Chen
// Test if every memory allocation pointer is 8-byte alignment
// Right behavior: print: All allocated blocks are 8-byte aligned.

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    // Initialize memory region
    if (Mem_Init(1024) != 0) {
        fprintf(stderr, "Mem_Init failed\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < 5; i++) {
        void* ptr = Mem_Alloc(21); 
        if (ptr == NULL) {
            fprintf(stderr, "Mem_Alloc failed\n");
            return EXIT_FAILURE;
        }
        
        printf("Allocated block at address: %p\n", ptr);
        
        // Check for 8-byte alignment
        if ((unsigned long)ptr % 8 != 0) {
            fprintf(stderr, "Memory is not 8-byte aligned: %p\n", ptr);
            return EXIT_FAILURE;
        }
    }
    
    printf("All allocated blocks are 8-byte aligned.\n");
    return EXIT_SUCCESS;
}
