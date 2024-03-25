/**
 * 12_init_round_one_page.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 12 - Initialize and round up to 1 page.
 *
 * Expected Result:
 * Success: Initialize and round up to 1 page test passed!
 */

#include <stdio.h>

#include "mem.h"

void init_and_round_up_one_page() {
    if (Mem_Init(2048) == 0) {
        printf("Success: Initialize and round up to 1 page test passed!\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("FAILURE: Initialize and round up to 1 page test failed!\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    init_and_round_up_one_page(); // Test
    return 0;
}