#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mem.h"

int main() {
    // Allocate memory
    uint8_t *ptr = (uint8_t *)malloc(sizeof(uint64_t));

    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Memory address: %p\n", (void *)ptr);

    // Check if memory address is 8-byte aligned
    if (((uintptr_t)ptr % 8) == 0) {
        printf("Memory address is 8-byte aligned\n");
    } else {
        printf("Memory address is not 8-byte aligned\n");
    }

    // Free allocated memory
    free(ptr);

    return 0;
}
