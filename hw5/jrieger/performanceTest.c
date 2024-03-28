#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mem.h"

#define NUM_ITERATIONS 2000000

int main() {
    // Initialize memory region
    if (Mem_Init(NUM_ITERATIONS * sizeof(int)) != 0) {
        fprintf(stderr, "Error: Failed to initialize memory\n");
        return EXIT_FAILURE;
    }

    clock_t start, end;
    double cpu_time_used_malloc, cpu_time_used_mem_alloc;

    // Performance testing with malloc
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int *ptr = malloc(sizeof(int));
        free(ptr);
    }
    end = clock();
    cpu_time_used_malloc = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Performance testing with Mem_Alloc
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int *ptr = Mem_Alloc(sizeof(int));
        Mem_Free(ptr, NO_COALESCE);
    }
    end = clock();
    cpu_time_used_mem_alloc = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken by malloc: %f seconds\n", cpu_time_used_malloc);
    printf("Time taken by Mem_Alloc: %f seconds\n", cpu_time_used_mem_alloc);

    return EXIT_SUCCESS;
}
