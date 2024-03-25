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

void test_try_to_free_null_pointer() {
    printf("Test: Try to free a NULL pointer\n");
    Mem_Free(NULL, TRUE); // Try to free a NULL pointer
    printf("Try to free a NULL pointer test passed!\n");
}

int main(){
    test_try_to_free_null_pointer();
    return 0;
}