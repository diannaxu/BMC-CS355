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

void test_alignment() {
    printf("Test: Checking for 8-byte alignment\n");
    if(Mem_Init(PAGE_SIZE) == FAIL) {
        printf("Initialization failed with errno %d\n", m_error);
        exit(EXIT_FAILURE);
    }
    void *ptr = Mem_Alloc(1);
    if ((uintptr_t)ptr % 8 == 0) {
        printf("Alignment test passed!\n");
    } else {
        printf("Alignment test failed!\n");
    }
    Mem_Dump(); // Dump to show mem_alloc was successful

}

int main(){
    test_alignment();
    return 0;
}