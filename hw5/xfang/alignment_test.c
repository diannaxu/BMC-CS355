/* 
    Author: Esther(Xinning) Fang
    Test whether memory is 8-byte aligned 
*/
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

int main() {
    // Test 1 with 1024 bytes
    if (Mem_Init(1024) == -1) {
        printf("Error when initializing.\n");
        exit(EXIT_FAILURE);
    }

    void *ptr1 = Mem_Alloc(4096);
    if (ptr1 == NULL) {
        printf("Error when allocating.\n");
        exit(EXIT_FAILURE);
    }
    if ((long)ptr1 % 8 != 0) {
        printf("Not 8-byte aligned.\n");
    } else {
        printf("8-byte aligned.\n");
    }

    // Test 2 with 1021 bytes
    void *ptr2 = Mem_Alloc(1021);
    if (ptr2 == NULL) {
        printf("Error when allocating.\n");
        exit(EXIT_FAILURE);
    }
    if ((long)ptr2 % 8 != 0) {
        printf("Not 8-byte aligned.\n");
    } else {
        printf("8-byte aligned.\n");
    }

    return EXIT_SUCCESS;
}