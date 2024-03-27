/**
 * 11_init_size_one_page.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 11 - Initialize with size of 1 page.
 *
 * Expected Result:
 * Success: Initialize with size of 1 page test passed!
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

void init_with_size_one_page() {
    if (Mem_Init(getpagesize()) == 0) {
        printf("Success: Initialize with size of 1 page test passed!\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Initialize with size of 1 page test failed!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Initialize memory alloc
    if (Mem_Init(1024) == -1) {
        printf("ERROR: Could not Mem_Init.\n");
        exit(EXIT_FAILURE);
    }

    init_with_size_one_page(); // Test
    return 0;
}