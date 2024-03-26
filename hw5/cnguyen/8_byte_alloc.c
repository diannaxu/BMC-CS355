// 8_byte_alloc.c
// Expected result: 8-byte alloc passed

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mem.h"

int main() {
    if (Mem_Init(1024) == -1) {
        printf("Mem_Init() failed\n");
        exit(EXIT_FAILURE);
    }

    void *ptr = Mem_Alloc(8);
    if ((uint64_t)ptr % 8 == 0) {
        printf("Pointer address: %p\n", ptr);
        printf("8-byte alloc passed\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("8-byte alloc failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
