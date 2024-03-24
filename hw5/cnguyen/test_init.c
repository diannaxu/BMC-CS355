#include <stdio.h>
#include "mem.h"

int main() {
    // Test Mem_Init with valid size
    printf("Testing Mem_Init with valid size...\n");
    if (Mem_Init(1024) == 0) {
        printf("Mem_Init successful.\n");
    } else {
        printf("Mem_Init failed.\n");
        return 1;
    }

    // Test Mem_Init with zero size
    printf("Testing Mem_Init with zero size...\n");
    if (Mem_Init(0) != 0) {
        printf("Mem_Init failed as expected with zero size.\n");
    } else {
        printf("Mem_Init succeeded unexpectedly with zero size.\n");
        return 1;
    }

    // Test Mem_Init with negative size
    printf("Testing Mem_Init with negative size...\n");
    if (Mem_Init(-100) != 0) {
        printf("Mem_Init failed as expected with negative size.\n");
    } else {
        printf("Mem_Init succeeded unexpectedly with negative size.\n");
        return 1;
    }

    // Test Mem_Init with size exceeding system limits
    printf("Testing Mem_Init with large size...\n");
    if (Mem_Init(100000000000000) != 0) {
        printf("Mem_Init failed as expected with size exceeding system limits.\n");
    } else {
        printf("Mem_Init succeeded unexpectedly with size exceeding system limits.\n");
        return 1;
    } 

    return 0;
}
