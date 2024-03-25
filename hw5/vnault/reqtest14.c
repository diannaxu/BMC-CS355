// 14th required test, this program checks to make sure that using
// Mem_Free with NULL on the memory, from a state of some chunks
// being allocated and others free, correctly does nothing
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "mem.h"

#define BYTES_TO_REQUEST 152
#define NUM_ALLOCS 8
#define FAILURE -1
#define BYTES8 8
#define BYTES16 16
#define BYTES32 32
#define BYTES64 64
#define NO_COALESCE 0

int main() {
    if (Mem_Init(BYTES_TO_REQUEST) == FAILURE) {
        if (m_error == E_BAD_ARGS) {
            printf("Mem_Init() failed, but correctly set m_error.\n");
            exit(EXIT_FAILURE);
        }
        else {
            printf("Mem_Init() failed, and did NOT correctly set m_error.\n");
            exit(EXIT_FAILURE);
        }
    }
    int bytes_to_alloc_array[NUM_ALLOCS] = {BYTES8, BYTES8, BYTES32, BYTES8, BYTES64, BYTES8, BYTES16, BYTES8};
    void * alloced_ptrs_array[NUM_ALLOCS];
    for (int i = 0; i < NUM_ALLOCS; i++) {
        alloced_ptrs_array[i] = Mem_Alloc(bytes_to_alloc_array[i]);
    }
    Mem_Free(alloced_ptrs_array[1], NO_COALESCE);
    Mem_Free(alloced_ptrs_array[2], NO_COALESCE);
    Mem_Free(alloced_ptrs_array[4], NO_COALESCE);
    Mem_Free(alloced_ptrs_array[6], NO_COALESCE);
    printf("The following Mem_Dump() should have several free regions.\n");
    Mem_Dump();
    if (Mem_Free(NULL, NO_COALESCE) == -1) {
        printf("Mem_Free incorrectly fails when given a NULL pointer (and flag %d)\n", NO_COALESCE);
        exit(EXIT_FAILURE);
    }
    printf("The following Mem_Dump() should be the exact same\n");
    Mem_Dump();
    return 0;
}
