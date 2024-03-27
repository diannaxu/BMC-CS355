/**
 * 14_free_null_pointer.c
 * Author: gchoe
 * Date: 3/24/2024
 * 
 * Description:
 * Test 14 - Try to free a NULL pointer.
 *
 * Expected Result:
 * Success: Try to free a NULL pointer test passed!
 */

#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

void try_to_free_NULL_ptr() {
    Mem_Free(NULL, 1); // Try to free a NULL ptr
    printf("Success: Try to free a NULL pointer test passed!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    try_to_free_NULL_ptr(); // Test
    return 0;
}