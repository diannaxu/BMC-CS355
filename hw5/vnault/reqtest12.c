// 12th required test, this program checks to make sure that Mem_Init
// correctly rounds up allocated space when not told to allocate an
// exact page size
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mem.h"

#define FAILURE -1

int main() {
    if (Mem_Init(getpagesize() / 8) == FAILURE) {
        if (m_error == E_BAD_ARGS) {
            printf("Mem_Init() failed, but correctly set m_error.\n");
            exit(EXIT_FAILURE);
        }
        else {
            printf("Mem_Init() failed, and did NOT correctly set m_error.\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("In the following Mem_Dump, there should be one chunk with exactly %d free space\n", getpagesize());
    return 0;
}
