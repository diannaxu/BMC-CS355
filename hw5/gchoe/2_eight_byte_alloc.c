/**
 * 2_eight_byte_alloc.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 2 - Simple 8-byte allocation.
 *
 * Expected Result:
 * Success: 8-byte allocation test passed!
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

void simple_eight_byte_alloc() {
    void *ptr = Mem_Alloc(8);

    if (ptr != NULL) {
        printf("Success: 8-byte allocation test passed!\n");
        Mem_Free(ptr, 1);
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: 8-byte allocation test failed!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init().\n");
        exit(EXIT_FAILURE);
    }

    simple_eight_byte_alloc(); // Test
    return 0;
}