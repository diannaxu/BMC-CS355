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

void test_memory_written_after_allocation() {
    printf("Test: Memory can be written to after allocation\n");
    void *ptr = Mem_Alloc(8);
    if (ptr != NULL) {
        printf("Allocation successful!\n");
        memset(ptr, 'A', 8); // Write to memory
        printf("Memory written successfully!\n");
        Mem_Free(ptr, TRUE); // Coalesce
    } else {
        printf("Allocation failed!\n");
    }
}

int main(){
    test_memory_written_after_allocation();
    return 0;
}