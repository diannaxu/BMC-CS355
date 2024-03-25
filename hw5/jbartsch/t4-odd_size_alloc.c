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

void test_odd_size_allocations() {
    printf("Test: Several odd-sized allocations\n");
    if(Mem_Init(PAGE_SIZE) == FAIL) {
        printf("Initialization failed with errno %d\n", m_error);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 5; i++) {
        void *ptr = Mem_Alloc(5 * (i + 1));
        if (ptr != NULL) {
            printf("Allocation %d successful!\n", i + 1);
        } else {
            printf("Allocation %d failed!\n", i + 1);
        }
    }
    Mem_Dump();
}

int main(){
    test_odd_size_allocations();
    return 0;
}