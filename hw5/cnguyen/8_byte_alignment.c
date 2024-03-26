// 8_byte_alignment.c
// Expected result: 8-byte alignment success

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mem.h"

int main() {
    if (Mem_Init(1024) == -1) {
        printf("Mem_Init() failed\n");
        exit(EXIT_FAILURE);
    }

    void *ptr1 = Mem_Alloc(3);
    void *ptr2 = Mem_Alloc(8);

    int r1 = (uint64_t)ptr1 % 8;
    int r2 = (uint64_t)ptr2 % 8;

    if (r1 == 0 && r2 == 0) {
        printf("Pointer 1 address: %p\n", ptr1);
        printf("Pointer 2 address: %p\n", ptr2);
        printf("8-byte alignment success\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("8-byte alignment failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
