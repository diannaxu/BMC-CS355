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

void test_no_space_left_to_allocate() {
    printf("Test: No space left to allocate\n");
    if (Mem_Init(PAGE_SIZE) == FAIL) {
        printf("Initialization failed!\n");
        exit(EXIT_FAILURE);
    }
    void *ptr = Mem_Alloc(2*PAGE_SIZE);
    if (ptr == NULL && m_error == E_NO_SPACE) {
        printf("No space left to allocate test passed!\n");
    } else {
        printf("No space left to allocate test failed!\n");
    }
    Mem_Dump();
}


int main(){
    test_no_space_left_to_allocate();
    return 0;
}