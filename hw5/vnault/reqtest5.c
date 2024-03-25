// Fifth required test, this program checks to make sure that Mem_Init
// correctly fails when used incorrectly
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mem.h"

#define BAD_BYTES_TO_REQUEST 0
#define BYTES_TO_REQUEST 1
#define FAILURE -1

int main() {
    if (Mem_Init(BAD_BYTES_TO_REQUEST) == FAILURE) {
        if (m_error == E_BAD_ARGS) {
            printf("Mem_Init() failed correctly when asking for %d byte(s), and correctly set m_error.\n", BAD_BYTES_TO_REQUEST);
        }
        else {
            printf("Mem_Init() failed correctly when asking for %d byte(s), but did NOT correctly set m_error.\n", BAD_BYTES_TO_REQUEST);
        }
    }
    else {
         printf("Mem_Init() should have failed when asking for %d byte(s), but did not.\n", BAD_BYTES_TO_REQUEST);
    }
    if (Mem_Init(BYTES_TO_REQUEST) == FAILURE) {
        if (m_error == E_BAD_ARGS) {
            printf("Mem_Init() failed INcorrectly when asking for %d byte(s), but correctly set m_error.\n", BYTES_TO_REQUEST);
            exit(EXIT_FAILURE);
        }
        else {
            printf("Mem_Init() failed INcorrectly when asking for %d byte(s), but correctly set m_error.\n", BYTES_TO_REQUEST);
            exit(EXIT_FAILURE);
        }
    }
    if (Mem_Init(BYTES_TO_REQUEST) == FAILURE) {
        if (m_error == E_BAD_ARGS) {
            printf("Mem_Init() failed correctly when calling more than once, and correctly set m_error.\n");
        }
        else {
            printf("Mem_Init() failed correctly when calling more than once, but did NOT correctly set m_error.\n");
        }
    }
    else {
        printf("Mem_Init() should have failed when calling more than once, but did not.\n");
    }
    return 0;
}
