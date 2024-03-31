#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include "mem.h"

#define NUM_BLOCKS 5
#define BLOCK_SIZE 64

int main() { //main for NO COALESCE
    // Initialize memory region
    if (Mem_Init(NUM_BLOCKS * BLOCK_SIZE) != 0) {
        fprintf(stderr, "Error: Failed to initialize memory\n");
        return EXIT_FAILURE;
    }

    void *block_ptrs[NUM_BLOCKS];

    // Allocate memory and store the pointers
    for (int i = 0; i < NUM_BLOCKS; i++) {
        block_ptrs[i] = Mem_Alloc(BLOCK_SIZE);
        if (block_ptrs[i] == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory\n");
            return EXIT_FAILURE;
        }
        // Write some data to the allocated memory block
        uint32_t my_num = 21474;
        void *writeTo = hide(block_ptrs[i]);
        writeTo = my_num;
    }
    // Free blocks without coalescing
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (Mem_Free(block_ptrs[i], NO_COALESCE) != 0) {
            fprintf(stderr, "Error: Failed to free memory\n");
            return EXIT_FAILURE;
        }
    }

    printf("Memory after freeing without coalescing:\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}

int main_0() { //main for COALESCE_ALL
    // Initialize memory region
    if (Mem_Init(NUM_BLOCKS * BLOCK_SIZE) != 0) {
        fprintf(stderr, "Error: Failed to initialize memory\n");
        return EXIT_FAILURE;
    }

    void *block_ptrs[NUM_BLOCKS];

    // Allocate memory and store the pointers
    for (int i = 0; i < NUM_BLOCKS; i++) {
        block_ptrs[i] = Mem_Alloc(BLOCK_SIZE);
        if (block_ptrs[i] == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory\n");
            return EXIT_FAILURE;
        }
        // Write some data to the allocated memory block
        uint32_t my_num = 21474;
        void *writeTo = hide(block_ptrs[i]);
        writeTo = my_num;
    }

    // Free blocks and coalesce all
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (Mem_Free(block_ptrs[i], COALESCE_ALL) != 0) {
            fprintf(stderr, "Error: Failed to free memory\n");
            return EXIT_FAILURE;
        }
    }

    printf("\nMemory after freeing and coalescing all:\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}

int main_1() { //main for COALESCE_FAST
    // Initialize memory region
    if (Mem_Init(NUM_BLOCKS * BLOCK_SIZE) != 0) {
        fprintf(stderr, "Error: Failed to initialize memory\n");
        return EXIT_FAILURE;
    }

    void *block_ptrs[NUM_BLOCKS];

    // Allocate memory and store the pointers
    for (int i = 0; i < NUM_BLOCKS; i++) {
        block_ptrs[i] = Mem_Alloc(BLOCK_SIZE);
        if (block_ptrs[i] == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory\n");
            return EXIT_FAILURE;
        }
        // Write some data to the allocated memory block
        uint32_t my_num = 21474;
        void *writeTo = hide(block_ptrs[i]);
        writeTo = my_num;
    }

    // Free blocks and coalesce fast
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (Mem_Free(block_ptrs[i], COALESCE_FAST) != 0) {
            fprintf(stderr, "Error: Failed to free memory\n");
            return EXIT_FAILURE;
        }
    }

    printf("\nMemory after freeing and coalescing fast:\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}
