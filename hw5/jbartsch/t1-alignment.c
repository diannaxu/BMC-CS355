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
    void *ptr = Mem_Alloc(1);
    if ((uintptr_t)ptr % 8 == 0) {
        printf("Alignment test passed!\n");
    } else {
        printf("Alignment test failed!\n");
    }
}

int main(){
    test_alignment();
    return 0;
}