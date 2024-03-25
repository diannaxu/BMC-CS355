/**
 * 5_bad_args_mem_init.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 5 - Bad args to Mem_Init().
 *
 * Expected Result:
 * Success: Bad args to Mem_Init() test passed!
 */

#include <stdio.h>

#include "mem.h"

void bad_args_mem_init() {
    if ((Mem_Init(0) == -1) && (Mem_Init(-1) == -1) && (Mem_Init(-20) == -1)) {
        printf("Success: Bad args to Mem_Init() test passed!\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Bad args to Mem_Init() test failed!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    bad_args_mem_init(); // Test
    return 0;
}