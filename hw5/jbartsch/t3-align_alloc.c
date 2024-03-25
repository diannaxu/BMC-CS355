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

void test_aligned_allocations() {
    printf("Test: Few aligned allocations\n");
    for (int i = 0; i < 5; i++) {
        void *ptr = Mem_Alloc(8);
        if ((uintptr_t)ptr % 8 == 0) {
            printf("Allocation %d successful!\n", i + 1);
        } else {
            printf("Allocation %d failed!\n", i + 1);
        }
    }
}

int main(){
    test_aligned_allocations();
    return 0;
}