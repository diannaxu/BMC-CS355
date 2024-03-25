// Seventh required test, this program checks to make sure that Free
// can coalesce correctly, doing this by allocating the entire memory,
// then freeing up chunks, and checking that contiguous chunks are
// coalesced
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
#define COALESCE_ALL 1

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
    Mem_Free(alloced_ptrs_array[5], COALESCE_ALL);
    printf("The following Mem_Dump() should have fewer free regions, and at least two should be size %d and %d\n", BYTES8 + BYTES32, BYTES64 + BYTES8 + BYTES16);
    Mem_Dump();
    return 0;
}
