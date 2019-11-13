/*
    Author: Esther(Xinning) Fang
    Make sure that no space is allocated when requested size is larger than any size of free chunks
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    if (Mem_Init(4096) == -1) {
        printf("Error when initilizing.\n");
        exit(EXIT_FAILURE);
    }

    // ptr1 and ptr2 will take up spaces with size of 32+3000+32+1000 = 4064
    void *ptr1 = Mem_Alloc(3000);
    void *ptr2 = Mem_Alloc(1000);
    // Only 32 bytes left 
    void *ptr3 = Mem_Alloc(100);
    if (ptr3 != NULL) {
        printf("Test failed: Should have no space to allocate ptr3.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("Test succeeded.\n");
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}
