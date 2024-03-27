/**
 * 10_odd_sized_alloc_free.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 10 - Odd-sized allocation and free.
 *
 * Expected Result:
 * Success: Odd-sized allocation and free test passed!
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

void odd_sized_alloc_free() {
    void *ptr = Mem_Alloc(13); // Allocate memory

    if (ptr != NULL) {
        printf("Success: Odd-sized allocation and free test passed!\n");
        Mem_Free(ptr, 1); // Free memory
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Odd-sized allocation and free test failed!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    odd_sized_alloc_free(); // Test
    return 0;
}