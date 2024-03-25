// First required test, this program checks to make sure that Mem_Init
// correctly rounds up to 8 bytes of memory when a user requests less
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mem.h"

#define BYTES_TO_REQUEST 1
#define BYTES_TO_ALLOC 1
#define FAILURE -1

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
    printf("The following number's last digit should be 0 or 8: %p\n", my_ptr);
    return 0;
}
