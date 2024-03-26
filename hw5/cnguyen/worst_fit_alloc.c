// worst_fit_alloc.c
// Expected result: Worst fit allocation success

#include <stdio.h>
#include <stdlib.h>
#include "mem.h" 

int main() {
    if (Mem_Init(4096) != 0) {
        printf("Mem_Init failed\n");
        exit(EXIT_FAILURE);
    }

    void* ptr1 = Mem_Alloc(1024); 
    void* ptr2 = Mem_Alloc(1409); 
    void* ptr3 = Mem_Alloc(512); 

    if (ptr1 == NULL || ptr2 == NULL || ptr3 == NULL) {
        printf("Mem_Alloc failed\n");
        return EXIT_FAILURE;
    }

    if (Mem_Free(ptr2, 0) != 0) {
        printf("Mem_Free failed\n");
        exit(EXIT_FAILURE);
    }

    void* worst_fit = Mem_Alloc(1024); 

    if (worst_fit == NULL) {
        printf("Mem_Alloc failed\n");
        exit(EXIT_FAILURE);
    }

    if (ptr2 == worst_fit) {
        printf("Worst fit allocation success\n");
        exit(EXIT_SUCCESS);
    }
}
