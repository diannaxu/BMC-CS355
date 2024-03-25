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

void test_initialize_with_1_page() {
    printf("Test: Initialize with size of 1 page\n");
    if (Mem_Init(PAGE_SIZE) == FAIL) {
        printf("Initialization failed!\n");
        exit(EXIT_FAILURE);
    }
    printf("Initialization successful!\n");
}

int main(){
    test_initialize_with_1_page();
    return 0;
}