// Eigth required test, this program checks to make sure that Mem_Alloc
// correctly allocates an amount of memory, then frees the space and
// prints the Mem_Dump() to confirm
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "mem.h"

#define BYTES_TO_REQUEST 42
#define BYTES_TO_ALLOC 8
#define FAILURE -1
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
    void * my_ptr = Mem_Alloc(BYTES_TO_ALLOC);
    if (my_ptr == NULL) {
        if (m_error == E_NO_SPACE) {
            printf("Mem_Alloc() failed, but correctly set m_error.\n");
        }
        else {
            printf("Mem_Alloc() failed, and did NOT correctly set m_error.\n");
        }
    }
    printf("Dumping Mem once...\n");
    Mem_Dump();
    Mem_Free(my_ptr, NO_COALESCE);
    printf("Dumping Mem twice...\n");
    Mem_Dump();
    printf("The second Mem Dump should have an extra free chunk, of size %d\n", BYTES_TO_ALLOC);
    return 0;
}
