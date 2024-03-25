/**
 * 1_eight_byte_align.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 1 - Check for 8-byte alignment.
 *
 * Expected Result:
 * Success: 8-byte alignment test passed!
 */

#include <stdint.h>
#include <stdio.h>

#include "mem.h"

void eight_byte_align() {
    void *ptr = Mem_Alloc(8);
    
    if ((uintptr_t)ptr % 8 == 0) {
        printf("Success: 8-byte alignment test passed!\n");
        Mem_Free(ptr, 1);
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: 8-byte alignment test failed!\n");
        Mem_Free(ptr, 1);
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init().\n");
        exit(EXIT_FAILURE);
    }

    eight_byte_align(); // Test

    return 0;
}