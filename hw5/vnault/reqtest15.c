// 15th required test, this program checks to make sure that the memory
// given by Mem_Alloc can be written to
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "mem.h"

#define BYTES_TO_REQUEST 8
#define BYTES_TO_ALLOC 8
#define FAILURE -1
#define VALUE_TO_WRITE 8

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
    uint8_t my_num = VALUE_TO_WRITE;
    my_ptr = my_num;
    printf("The following number should be %d: %u\n", VALUE_TO_WRITE, my_ptr);
    return 0;
}
