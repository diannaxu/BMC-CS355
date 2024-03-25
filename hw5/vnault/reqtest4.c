// Fourth required test, this program checks to make sure that Mem_Alloc
// can correctly allocate several NON-8-byte-aligned requests in sequence,
// and tests by writing to the returned pointers, and reading back the values
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "mem.h"

#define BYTES_TO_REQUEST 64
#define BYTES8 8
#define BYTES6 6
#define BYTES16 16
#define BYTES15 15
#define BYTES27 27
#define FAILURE -1
#define BYTES8_VAL_TO_WRITE1 0
#define BYTES8_VAL_TO_WRITE2 250
#define BYTES16_VAL_TO_WRITE 340
#define BYTES32_VAL_TO_WRITE 70000

void perform_allocation(int bytes_to_alloc, int num_allocation, int val_to_write) {
    void * my_ptr = Mem_Alloc(bytes_to_alloc);
    if (my_ptr == NULL) {
        if (m_error == E_NO_SPACE) {
            printf("Mem_Alloc() failed on allocation %d, but correctly set m_error.\n", num_allocation);
        }
        else {
            printf("Mem_Alloc() failed on allocation %d, and did NOT correctly set m_error.\n", num_allocation);
        }
    }
    if (bytes_to_alloc == BYTES8) {
        uint8_t my_num = (uint8_t) val_to_write;
        my_ptr = my_num;
    }
    if (bytes_to_alloc == BYTES16) {
        uint16_t my_num = (uint16_t) val_to_write;
         my_ptr = my_num;
    }
    if (bytes_to_alloc == BYTES16) {
        uint32_t my_num = (uint32_t) val_to_write;
         my_ptr = my_num;
    }
    printf("Allocation number %d - The following number should be %d: %u\n", num_allocation, val_to_write, my_ptr);
}

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
    perform_allocation(BYTES6, 1, BYTES8_VAL_TO_WRITE1);
    perform_allocation(BYTES6, 2, BYTES8_VAL_TO_WRITE2);
    perform_allocation(BYTES15, 3, BYTES16_VAL_TO_WRITE);
    perform_allocation(BYTES27, 4, BYTES32_VAL_TO_WRITE);
    return 0;
}
