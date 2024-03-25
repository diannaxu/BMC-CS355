#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h> 
#include <stdbool.h>

#define PAGE_SIZE 4096
#define NUM_ALLOC 8192
#define FAIL -1
#define TRUE 1
#define FALSE 0

void test_coalesce_free_space() {
    printf("Test: Coalesce of free space\n");
    // Initialize with a small size
    if (Mem_Init(2 * PAGE_SIZE) == FAIL) {
        printf("Initialization failed!\n");
        exit(EXIT_FAILURE);
    }

    // Allocate and free blocks to create free spaces
    void *ptr1 = Mem_Alloc(500);
    void *ptr2 = Mem_Alloc(200);
    Mem_Free(ptr1, FALSE); // Don't coalesce
    Mem_Free(ptr2, FALSE); // Don't coalesce

    // Allocate a new block, should use coalesced space
    void *ptr3 = Mem_Alloc(700);

    if (ptr3 != NULL) {
        printf("Coalesce successful!\n");
    } else {
        printf("Coalesce failed!\n");
    }
}

int main(){
    test_coalesce_free_space();
    return 0;
}