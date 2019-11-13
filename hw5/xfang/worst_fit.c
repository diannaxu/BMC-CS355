/*
    Author: Esther(Xinning) Fang
    Given two free chunks, check if Mem_Alloc() takes the chunk with the largest size
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

    void *ptr1 = Mem_Alloc(16);
    if (ptr1 == NULL) {
        printf("Error during allocation.\n");
        exit(EXIT_FAILURE);
    }
    Mem_Free(ptr1, 0);
    Mem_Dump();

    // Even though only 8 bytes is needed, worst fit will take the second chunk
    // and split it as it is larger
    void *ptr2 = Mem_Alloc(8);
    if (ptr2 == NULL) {
        printf("Error during allocation.\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    return EXIT_SUCCESS;
}
