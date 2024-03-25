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

void test_simple_alloc_and_free() {
    printf("Test: Simple allocation and free\n");
    if(Mem_Init(PAGE_SIZE) == FAIL) {
        printf("Initialization failed with errno %d\n", m_error);
        exit(EXIT_FAILURE);
    }
    void *ptr = Mem_Alloc(8);
    if (ptr != NULL) {
        printf("Allocation successful!\n");
        Mem_Free(ptr, TRUE); // Coalesce
        printf("Free successful!\n");
    } else {
        printf("Allocation failed!\n");
    }
    Mem_Dump();
}

int main(){
    test_simple_alloc_and_free();
    return 0;
}