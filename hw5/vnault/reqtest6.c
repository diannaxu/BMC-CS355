// Sixth required test, this program checks to make sure that Mem_Alloc
// correctly uses the worst fitting section of memory to allocate new
// memory, doing this by allocating the entire memory, then freeing up
// chunks, and checking that an allocation uses memory from the largest
// free chunk
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "mem.h"

#define BYTES_TO_REQUEST 144
#define NUM_ALLOCS 7
#define FAILURE -1
#define VALUE_TO_WRITE 47
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
    int bytes_to_alloc_array[NUM_ALLOCS] = {BYTES8, BYTES32, BYTES8, BYTES64, BYTES8, BYTES16, BYTES8};
    void * alloced_ptrs_array[NUM_ALLOCS];
    for (int i = 0; i < NUM_ALLOCS; i++) {
        alloced_ptrs_array[i] = Mem_Alloc(bytes_to_alloc_array[i]);
    }
    for (int j = 1; j < NUM_ALLOCS; j = j + 2) {
        Mem_Free(alloced_ptrs_array[j], NO_COALESCE);
    }
    printf("The following Mem_Dump() should have several differently sized free regions.\n");
    Mem_Dump();
    Mem_Alloc(BYTES8);
    printf("The following Mem_Dump() should have the largest free region from before reduced in size.\n");
    Mem_Dump();
    return 0;
}
