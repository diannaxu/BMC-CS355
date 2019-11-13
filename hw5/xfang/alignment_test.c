/*
    Author: Esther(Xinning) Fang
    Test whether memory is 8-byte aligned
*/
#include <stdio.h>
#include <stdlib.h>
#include "../mem.h"

int main() {
    if (Mem_Init(4096) == -1) {
        printf("Error when initializing.\n");
        exit(EXIT_FAILURE);
    }

    // test 1 with 16 bytes
    // no need to round
    void *ptr1 = Mem_Alloc(16);
    if (ptr1 == NULL) {
        printf("Error when allocating.\n");
        exit(EXIT_FAILURE);
    }
    printf("pointer to ptr1: %p\n", ptr1);

    // Test 2 with 1021 bytes
    // round it to 1024 bytes
    void *ptr2 = Mem_Alloc(1021);
    if (ptr2 == NULL) {
        printf("Error when allocating.\n");
        exit(EXIT_FAILURE);
    }
    printf("pointer to ptr2: %p\n", ptr2);

    return EXIT_SUCCESS;
}