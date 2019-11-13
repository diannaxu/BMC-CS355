/*
    Author: Esther(Xinning) Fang
    Aligned odd-sized allocations and frees
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    if (Mem_Init(4096) == -1) {
        printf("Error when initializing.\n");
        exit(EXIT_FAILURE);
    }

    // 16-byte allocation
    void *ptr1 = Mem_Alloc(16);
    if (ptr1 == NULL) {
        printf("Error during 16-byte allocation.\n");
        exit(EXIT_FAILURE);
    }

    // 1-byte allocation
    // 8 bytes will be allocated
    void *ptr2 = Mem_Alloc(1);
    if (ptr2 == NULL) {
        printf("Error during 1-byte allocation.\n");
        exit(EXIT_FAILURE);
    }

    // 23-byte allocation
    // 24 bytes will be allocated
    void *ptr3 = Mem_Alloc(23);
    if (ptr3 == NULL) {
        printf("Error during 23-byte allocation.\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();
    
    if (Mem_Free(ptr1, 0) == -1) {
        printf("Error when freeing the 8-byte allocation.\n");
        exit(EXIT_FAILURE);
    }
    if (Mem_Free(ptr2, 0) == -1) {
        printf("Error when freeing the 8-byte allocation.\n");
        exit(EXIT_FAILURE);
    }
    if (Mem_Free(ptr3, 0) == -1) {
        printf("Error when freeing the 8-byte allocation.\n");
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    return EXIT_SUCCESS;
}
