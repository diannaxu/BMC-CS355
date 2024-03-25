// 13th required test, this program checks to make sure that Mem_Alloc
// correctly fails when it tries to allocate more space when there is
// none left
// Victor Nault

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mem.h"

#define FAILURE -1
#define TRUE 1
#define BYTES_TO_ALLOC 1

int main() {
    if (Mem_Init(getpagesize()) == FAILURE) {
        if (m_error == E_BAD_ARGS) {
            printf("Mem_Init() failed, but correctly set m_error.\n");
            exit(EXIT_FAILURE);
        }
        else {
            printf("Mem_Init() failed, and did NOT correctly set m_error.\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("If the following loop lasts forever, then Mem_Alloc is not correctly failing when it runs out of space\n");
    int counter = 0;
    while (TRUE) {
        if (Mem_Alloc(BYTES_TO_ALLOC) == NULL) {
            break;
        }
        counter = counter + BYTES_TO_ALLOC;
    }
    if (m_error == E_NO_SPACE) {
        printf("Mem_Alloc allocated %d bytes before running out of space, from an initial pool of %d bytes. m_error was set correctly", counter, getpagesize());
    }
    else {
        printf("Mem_Alloc allocated %d bytes before running out of space, from an initial pool of %d bytes. m_error was NOT set correctly", counter, getpagesize());
    }
    return 0;
}
