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

void test_worstfit_allocation() {
    printf("Test: Worstfit allocation\n");
    // Initialize with a small size
    if (Mem_Init(5 * PAGE_SIZE) == FAIL) {
        printf("Initialization failed!\n");
        exit(EXIT_FAILURE);
    }

    // Allocate several blocks
    void *ptr1 = Mem_Alloc(500);
    void *ptr2 = Mem_Alloc(200);
    void *ptr3 = Mem_Alloc(1000);

    if (ptr1 != NULL && ptr2 != NULL && ptr3 != NULL) {
        printf("Allocations successful!\n");
    } else {
        printf("Allocations failed!\n");
    }
    Mem_Dump();
}

int main(){
    test_worstfit_allocation();
    return 0;
}